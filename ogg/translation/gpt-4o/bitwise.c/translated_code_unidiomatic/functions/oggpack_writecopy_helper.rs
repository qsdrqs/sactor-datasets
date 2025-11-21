use libc::{c_int, c_long, c_uchar, memmove, realloc};
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
    let mut bits = bits - bytes * 8;
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
