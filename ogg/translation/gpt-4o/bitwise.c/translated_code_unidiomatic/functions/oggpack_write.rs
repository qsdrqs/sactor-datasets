use libc::{c_int, c_long, c_uchar, realloc};
pub unsafe fn oggpack_write(b: *mut oggpack_buffer, value: u32, bits: c_int) {
    const LONG_MAX: c_long = c_long::MAX;
    if bits < 0 || bits > 32 {
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
    let mut value = value & mask[bits as usize];
    let mut bits = bits + (*b).endbit;
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
