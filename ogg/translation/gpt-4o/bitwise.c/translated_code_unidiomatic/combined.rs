use libc::c_int;
use libc::c_long;
use libc::c_uchar;
use libc::c_void;
use libc::free;
use libc::malloc;
use libc::memmove;
use libc::memset;
use libc::realloc;
use std::i64;
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct oggpack_buffer {
    pub endbyte: libc::c_long,
    pub endbit: libc::c_int,
    pub buffer: *mut libc::c_uchar,
    pub ptr: *mut libc::c_uchar,
    pub storage: libc::c_long,
}
static mask: [u32; 33] = [
    0x00000000, 0x00000001, 0x00000003, 0x00000007, 0x0000000f, 0x0000001f, 0x0000003f, 0x0000007f,
    0x000000ff, 0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff, 0x00001fff, 0x00003fff, 0x00007fff,
    0x0000ffff, 0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff, 0x001fffff, 0x003fffff, 0x007fffff,
    0x00ffffff, 0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff, 0x1fffffff, 0x3fffffff, 0x7fffffff,
    0xffffffff,
];
static mask8B: [u32; 9] = [0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff];
pub unsafe fn oggpack_writeinit(b: *mut oggpack_buffer) {
    if b.is_null() {
        return;
    }
    memset(
        b as *mut libc::c_void,
        0,
        std::mem::size_of::<oggpack_buffer>(),
    );
    let buffer = malloc(256) as *mut c_uchar;
    if buffer.is_null() {
        return;
    }
    (*b).buffer = buffer;
    (*b).ptr = buffer;
    *(*b).buffer = b'\0' as c_uchar;
    (*b).storage = 256;
}
pub unsafe fn oggpackB_writeinit(b: *mut oggpack_buffer) {
    oggpack_writeinit(b);
}
pub unsafe fn oggpack_writecheck(b: *mut oggpack_buffer) -> libc::c_int {
    if (*b).ptr.is_null() || (*b).storage == 0 {
        return -1;
    }
    0
}
pub unsafe fn oggpackB_writecheck(b: *mut oggpack_buffer) -> libc::c_int {
    oggpack_writecheck(b)
}
pub unsafe fn oggpack_writetrunc(b: *mut oggpack_buffer, bits: libc::c_long) {
    let bytes = bits >> 3;
    if !(*b).ptr.is_null() {
        let bits = bits - bytes * 8;
        (*b).ptr = (*b).buffer.offset(bytes as isize);
        (*b).endbit = bits as libc::c_int;
        (*b).endbyte = bytes;
        *(*b).ptr &= mask[bits as usize] as libc::c_uchar;
    }
}
pub unsafe fn oggpackB_writetrunc(b: *mut oggpack_buffer, bits: libc::c_long) {
    let bytes = bits >> 3;
    if !(*b).ptr.is_null() {
        let bits = bits - bytes * 8;
        (*b).ptr = (*b).buffer.offset(bytes as isize);
        (*b).endbit = bits as libc::c_int;
        (*b).endbyte = bytes;
        *(*b).ptr &= mask8B[bits as usize] as libc::c_uchar;
    }
}
pub unsafe fn oggpack_write(b: *mut oggpack_buffer, value: u32, bits: c_int) {
    const LONG_MAX: c_long = c_long::MAX;
    if !(0..=32).contains(&bits) {
        oggpack_writeclear(b);
        return;
    }
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).ptr.is_null() {
            return;
        }
        if (*b).storage > LONG_MAX - 256 {
            oggpack_writeclear(b);
            return;
        }
        let ret = realloc(
            (*b).buffer as *mut libc::c_void,
            ((*b).storage + 256) as usize,
        );
        if ret.is_null() {
            oggpack_writeclear(b);
            return;
        }
        (*b).buffer = ret as *mut c_uchar;
        (*b).storage += 256;
        (*b).ptr = (*b).buffer.offset((*b).endbyte as isize);
    }
    let value = value & mask[bits as usize];
    let bits = bits + (*b).endbit;
    *(*b).ptr.offset(0) |= (value << (*b).endbit) as c_uchar;
    if bits >= 8 {
        *(*b).ptr.offset(1) = (value >> (8 - (*b).endbit)) as c_uchar;
        if bits >= 16 {
            *(*b).ptr.offset(2) = (value >> (16 - (*b).endbit)) as c_uchar;
            if bits >= 24 {
                *(*b).ptr.offset(3) = (value >> (24 - (*b).endbit)) as c_uchar;
                if bits >= 32 {
                    if (*b).endbit != 0 {
                        *(*b).ptr.offset(4) = (value >> (32 - (*b).endbit)) as c_uchar;
                    } else {
                        *(*b).ptr.offset(4) = 0;
                    }
                }
            }
        }
    }
    (*b).endbyte += (bits / 8) as c_long;
    (*b).ptr = (*b).ptr.offset((bits / 8) as isize);
    (*b).endbit = bits & 7;
}
pub unsafe fn oggpackB_write(b: *mut oggpack_buffer, mut value: u32, bits: c_int) {
    if !(0..=32).contains(&bits) {
        oggpack_writeclear(b);
        return;
    }
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).ptr.is_null() {
            return;
        }
        if (*b).storage > i64::MAX - 256 {
            oggpack_writeclear(b);
            return;
        }
        let ret = realloc(
            (*b).buffer as *mut libc::c_void,
            ((*b).storage + 256) as usize,
        );
        if ret.is_null() {
            oggpack_writeclear(b);
            return;
        }
        (*b).buffer = ret as *mut c_uchar;
        (*b).storage += 256;
        (*b).ptr = (*b).buffer.offset((*b).endbyte as isize);
    }
    if bits > 0 {
        value = (value & mask[bits as usize]) << (32 - bits);
    }
    let total_bits = bits + (*b).endbit;
    *(*b).ptr.offset(0) |= (value >> (24 + (*b).endbit)) as c_uchar;
    if total_bits >= 8 {
        *(*b).ptr.offset(1) = (value >> (16 + (*b).endbit)) as c_uchar;
        if total_bits >= 16 {
            *(*b).ptr.offset(2) = (value >> (8 + (*b).endbit)) as c_uchar;
            if total_bits >= 24 {
                *(*b).ptr.offset(3) = (value >> (*b).endbit) as c_uchar;
                if total_bits >= 32 {
                    if (*b).endbit != 0 {
                        *(*b).ptr.offset(4) = (value << (8 - (*b).endbit)) as c_uchar;
                    } else {
                        *(*b).ptr.offset(4) = 0;
                    }
                }
            }
        }
    }
    (*b).endbyte += (total_bits / 8) as c_long;
    (*b).ptr = (*b).ptr.offset((total_bits / 8) as isize);
    (*b).endbit = total_bits & 7;
}
pub unsafe fn oggpack_writealign(b: *mut oggpack_buffer) {
    let bits = 8 - (*b).endbit;
    if bits < 8 {
        oggpack_write(b, 0, bits);
    }
}
pub unsafe fn oggpackB_writealign(b: *mut oggpack_buffer) {
    let bits: c_int = 8 - (*b).endbit;
    if bits < 8 {
        oggpackB_write(b, 0, bits);
    }
}
pub unsafe fn oggpack_writecopy_helper(
    b: *mut oggpack_buffer,
    source: *mut libc::c_void,
    bits: c_long,
    w: unsafe extern "C" fn(*mut oggpack_buffer, libc::c_ulong, c_int),
    msb: c_int,
) {
    let ptr = source as *mut c_uchar;
    let bytes = bits / 8;
    let pbytes = ((*b).endbit as c_long + bits) / 8;
    let bits = bits - bytes * 8;
    if (*b).endbyte + pbytes >= (*b).storage {
        if (*b).ptr.is_null() {
            oggpack_writeclear(b);
            return;
        }
        if (*b).storage > (*b).endbyte + pbytes + 256 {
            oggpack_writeclear(b);
            return;
        }
        (*b).storage = (*b).endbyte + pbytes + 256;
        let ret = realloc((*b).buffer as *mut libc::c_void, (*b).storage as usize);
        if ret.is_null() {
            oggpack_writeclear(b);
            return;
        }
        (*b).buffer = ret as *mut c_uchar;
        (*b).ptr = (*b).buffer.offset((*b).endbyte as isize);
    }
    if (*b).endbit != 0 {
        for i in 0..bytes {
            w(b, *ptr.offset(i as isize) as libc::c_ulong, 8);
        }
    } else {
        memmove((*b).ptr as *mut libc::c_void, source, bytes as usize);
        (*b).ptr = (*b).ptr.offset(bytes as isize);
        (*b).endbyte += bytes;
        *(*b).ptr = 0;
    }
    if bits != 0 {
        if msb != 0 {
            w(
                b,
                (*ptr.offset(bytes as isize) >> (8 - bits)) as libc::c_ulong,
                bits as c_int,
            );
        } else {
            w(
                b,
                *ptr.offset(bytes as isize) as libc::c_ulong,
                bits as c_int,
            );
        }
    }
}
pub unsafe fn oggpack_writecopy(b: *mut oggpack_buffer, source: *mut c_void, bits: c_long) {
    unsafe extern "C" fn oggpack_write_wrapper(
        b: *mut oggpack_buffer,
        value: libc::c_ulong,
        bits: libc::c_int,
    ) {
        unsafe {
            oggpack_write(b, value as u32, bits);
        }
    }
    oggpack_writecopy_helper(b, source, bits, oggpack_write_wrapper, 0);
}
pub unsafe fn oggpackB_writecopy(b: *mut oggpack_buffer, source: *mut c_void, bits: c_long) {
    extern "C" {
        fn oggpackB_write(b: *mut oggpack_buffer, value: libc::c_ulong, bits: libc::c_int);
    }
    oggpack_writecopy_helper(b, source, bits, oggpackB_write, 1);
}
pub unsafe fn oggpack_reset(b: *mut oggpack_buffer) {
    if (*b).ptr.is_null() {
        return;
    }
    (*b).ptr = (*b).buffer;
    *(*b).buffer = 0;
    (*b).endbit = 0;
    (*b).endbyte = 0;
}
pub unsafe fn oggpackB_reset(b: *mut oggpack_buffer) {
    oggpack_reset(b);
}
pub unsafe fn oggpack_writeclear(b: *mut oggpack_buffer) {
    if !(*b).buffer.is_null() {
        free((*b).buffer as *mut c_void);
    }
    memset(b as *mut c_void, 0, std::mem::size_of::<oggpack_buffer>());
}
pub unsafe fn oggpackB_writeclear(b: *mut oggpack_buffer) {
    oggpack_writeclear(b);
}
pub unsafe fn oggpack_readinit(
    b: *mut oggpack_buffer,
    buf: *mut libc::c_uchar,
    bytes: libc::c_int,
) {
    unsafe fn memset(ptr: *mut libc::c_void, value: libc::c_int, num: libc::size_t) {
        libc::memset(ptr, value, num);
    }
    memset(
        b as *mut libc::c_void,
        0,
        std::mem::size_of::<oggpack_buffer>(),
    );
    (*b).buffer = buf;
    (*b).ptr = buf;
    (*b).storage = bytes as libc::c_long;
}
pub unsafe fn oggpackB_readinit(
    b: *mut oggpack_buffer,
    buf: *mut libc::c_uchar,
    bytes: libc::c_int,
) {
    oggpack_readinit(b, buf, bytes);
}
pub unsafe fn oggpack_look(b: *mut oggpack_buffer, bits: libc::c_int) -> libc::c_long {
    if !(0..=32).contains(&bits) {
        return -1;
    }
    let m = mask[bits as usize] as libc::c_ulong;
    let bits = bits + (*b).endbit;
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).endbyte > (*b).storage - ((bits + 7) as libc::c_long >> 3) {
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    let mut ret = *(*b).ptr.offset(0) as libc::c_ulong >> (*b).endbit;
    if bits > 8 {
        ret |= (*(*b).ptr.offset(1) as libc::c_ulong) << (8 - (*b).endbit);
        if bits > 16 {
            ret |= (*(*b).ptr.offset(2) as libc::c_ulong) << (16 - (*b).endbit);
            if bits > 24 {
                ret |= (*(*b).ptr.offset(3) as libc::c_ulong) << (24 - (*b).endbit);
                if bits > 32 && (*b).endbit != 0 {
                    ret |= (*(*b).ptr.offset(4) as libc::c_ulong) << (32 - (*b).endbit);
                }
            }
        }
    }
    (m & ret) as libc::c_long
}
pub unsafe fn oggpackB_look(b: *mut oggpack_buffer, bits: libc::c_int) -> libc::c_long {
    let mut ret: libc::c_ulong;
    let m = 32 - bits;
    if !(0..=32).contains(&m) {
        return -1;
    }
    let bits = bits + (*b).endbit;
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).endbyte > (*b).storage - ((bits as libc::c_long + 7) >> 3) {
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    ret = (*(*b).ptr.offset(0) as libc::c_ulong) << (24 + (*b).endbit);
    if bits > 8 {
        ret |= (*(*b).ptr.offset(1) as libc::c_ulong) << (16 + (*b).endbit);
        if bits > 16 {
            ret |= (*(*b).ptr.offset(2) as libc::c_ulong) << (8 + (*b).endbit);
            if bits > 24 {
                ret |= (*(*b).ptr.offset(3) as libc::c_ulong) << (*b).endbit;
                if bits > 32 && (*b).endbit != 0 {
                    ret |= (*(*b).ptr.offset(4) as libc::c_ulong) >> (8 - (*b).endbit);
                }
            }
        }
    }
    (((ret & 0xffffffff) >> (m >> 1)) >> ((m + 1) >> 1)) as libc::c_long
}
pub unsafe fn oggpack_look1(b: *mut oggpack_buffer) -> libc::c_long {
    if (*b).endbyte >= (*b).storage {
        return -1;
    }
    ((*(*b).ptr >> (*b).endbit) & 1) as libc::c_long
}
pub unsafe fn oggpackB_look1(b: *mut oggpack_buffer) -> libc::c_long {
    if (*b).endbyte >= (*b).storage {
        return -1;
    }
    ((*(*b).ptr >> (7 - (*b).endbit)) & 1) as libc::c_long
}
pub unsafe fn oggpack_adv(b: *mut oggpack_buffer, bits: libc::c_int) {
    let bits = bits + (*b).endbit;
    if (*b).endbyte > (*b).storage - (((bits + 7) >> 3) as libc::c_long) {
        (*b).ptr = std::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
        return;
    }
    (*b).ptr = (*b).ptr.add((bits / 8) as usize);
    (*b).endbyte += (bits / 8) as libc::c_long;
    (*b).endbit = bits & 7;
}
pub unsafe fn oggpackB_adv(b: *mut oggpack_buffer, bits: libc::c_int) {
    oggpack_adv(b, bits);
}
pub unsafe fn oggpack_adv1(b: *mut oggpack_buffer) {
    if !b.is_null() {
        (*b).endbit += 1;
        if (*b).endbit > 7 {
            (*b).endbit = 0;
            (*b).ptr = (*b).ptr.add(1);
            (*b).endbyte += 1;
        }
    }
}
pub unsafe fn oggpackB_adv1(b: *mut oggpack_buffer) {
    oggpack_adv1(b);
}
pub unsafe fn oggpack_read(b: *mut oggpack_buffer, bits: c_int) -> c_long {
    let mut ret: c_long;
    
    if !(0..=32).contains(&bits) {
        goto_err(b);
        return -1;
    }
    let m: u32 = mask[bits as usize];
    let bits = bits + (*b).endbit;
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).endbyte > (*b).storage - (((bits + 7) as c_long) >> 3) {
            goto_err(b);
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    ret = (*(*b).ptr.offset(0) as c_long) >> (*b).endbit;
    if bits > 8 {
        ret |= ((*(*b).ptr.offset(1) as c_long) << (8 - (*b).endbit)) as c_long;
        if bits > 16 {
            ret |= ((*(*b).ptr.offset(2) as c_long) << (16 - (*b).endbit)) as c_long;
            if bits > 24 {
                ret |= ((*(*b).ptr.offset(3) as c_long) << (24 - (*b).endbit)) as c_long;
                if bits > 32 && (*b).endbit != 0 {
                    ret |= ((*(*b).ptr.offset(4) as c_long) << (32 - (*b).endbit)) as c_long;
                }
            }
        }
    }
    ret &= m as c_long;
    (*b).ptr = (*b).ptr.offset((bits / 8) as isize);
    (*b).endbyte += (bits / 8) as c_long;
    (*b).endbit = bits & 7;
    return ret;
    unsafe fn goto_err(b: *mut oggpack_buffer) {
        (*b).ptr = std::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
    }
}
pub unsafe fn oggpackB_read(b: *mut oggpack_buffer, bits: libc::c_int) -> libc::c_long {
    let mut ret: libc::c_long;
    let m = 32 - bits;
    if !(0..=32).contains(&m) {
        goto_err(b);
        return -1;
    }
    let bits = bits + (*b).endbit;
    if (*b).endbyte + 4 >= (*b).storage {
        if (*b).endbyte > (*b).storage - ((bits as libc::c_long + 7) >> 3) {
            goto_err(b);
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    ret = (*(*b).ptr.offset(0) as libc::c_long) << (24 + (*b).endbit);
    if bits > 8 {
        ret |= (*(*b).ptr.offset(1) as libc::c_long) << (16 + (*b).endbit);
        if bits > 16 {
            ret |= (*(*b).ptr.offset(2) as libc::c_long) << (8 + (*b).endbit);
            if bits > 24 {
                ret |= (*(*b).ptr.offset(3) as libc::c_long) << (*b).endbit;
                if bits > 32 && (*b).endbit != 0 {
                    ret |= (*(*b).ptr.offset(4) as libc::c_long) >> (8 - (*b).endbit);
                }
            }
        }
    }
    ret = ((ret & 0xffffffff) >> (m >> 1)) >> ((m + 1) >> 1);
    (*b).ptr = (*b).ptr.offset(bits as isize / 8);
    (*b).endbyte += bits as libc::c_long / 8;
    (*b).endbit = bits & 7;
    return ret;
    unsafe fn goto_err(b: *mut oggpack_buffer) {
        (*b).ptr = std::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
    }
}
pub unsafe fn oggpack_read1(b: *mut oggpack_buffer) -> libc::c_long {
    let ret: libc::c_long;
    if (*b).endbyte >= (*b).storage {
        goto_overflow(b);
        return -1;
    }
    ret = ((*(*b).ptr >> (*b).endbit) & 1) as libc::c_long;
    (*b).endbit += 1;
    if (*b).endbit > 7 {
        (*b).endbit = 0;
        (*b).ptr = (*b).ptr.add(1);
        (*b).endbyte += 1;
    }
    return ret;
    unsafe fn goto_overflow(b: *mut oggpack_buffer) {
        (*b).ptr = std::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
    }
}
pub unsafe fn oggpackB_read1(b: *mut oggpack_buffer) -> libc::c_long {
    fn overflow(b: *mut oggpack_buffer) -> libc::c_long {
        unsafe {
            (*b).ptr = std::ptr::null_mut();
            (*b).endbyte = (*b).storage;
            (*b).endbit = 1;
        }
        -1
    }
    if (*b).endbyte >= (*b).storage {
        overflow(b)
    } else {
        let ret = ((*(*b).ptr) >> (7 - (*b).endbit)) & 1;
        (*b).endbit += 1;
        if (*b).endbit > 7 {
            (*b).endbit = 0;
            (*b).ptr = (*b).ptr.add(1);
            (*b).endbyte += 1;
        }
        ret as libc::c_long
    }
}
pub unsafe fn oggpack_bytes(b: *mut oggpack_buffer) -> libc::c_long {
    let b_ref = &*b;
    b_ref.endbyte + ((b_ref.endbit as libc::c_long) + 7) / 8
}
pub unsafe fn oggpack_bits(b: *mut oggpack_buffer) -> libc::c_long {
    let b_ref = &*b;
    b_ref.endbyte * 8 + b_ref.endbit as libc::c_long
}
pub fn oggpackB_bytes(b: *mut oggpack_buffer) -> libc::c_long {
    unsafe { oggpack_bytes(b) }
}
pub unsafe fn oggpackB_bits(b: *mut oggpack_buffer) -> libc::c_long {
    oggpack_bits(b)
}
pub unsafe fn oggpack_get_buffer(b: *mut oggpack_buffer) -> *mut libc::c_uchar {
    (*b).buffer
}
pub unsafe fn oggpackB_get_buffer(b: *mut oggpack_buffer) -> *mut libc::c_uchar {
    oggpack_get_buffer(b)
}
