pub unsafe fn oggpack_writecopy_helper(
    b: *mut oggpack_buffer,
    source: *mut libc::c_void,
    mut bits: libc::c_long,
    w: unsafe extern "C" fn(*mut oggpack_buffer, libc::c_ulong, libc::c_int),
    msb: libc::c_int,
) {
    let ptr = source as *mut libc::c_uchar;
    let bytes = bits / 8;
    let pbytes = ((*b).endbit as libc::c_long + bits) / 8;
    bits -= bytes * 8;
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
        let ret = libc::realloc((*b).buffer as *mut libc::c_void, (*b).storage as usize);
        if ret.is_null() {
            oggpack_writeclear(b);
            return;
        }
        (*b).buffer = ret as *mut libc::c_uchar;
        (*b).ptr = (*b).buffer.offset((*b).endbyte as isize);
    }
    if (*b).endbit != 0 {
        let mut i: libc::c_long = 0;
        while i < bytes {
            let val = *ptr.offset(i as isize) as libc::c_ulong;
            w(b, val, 8 as libc::c_int);
            i += 1;
        }
    } else {
        libc::memmove(
            (*b).ptr as *mut libc::c_void,
            source as *const libc::c_void,
            bytes as usize,
        );
        (*b).ptr = (*b).ptr.add(bytes as usize);
        (*b).endbyte += bytes;
        *(*b).ptr = 0;
    }
    if bits != 0 {
        let byte = *ptr.offset(bytes as isize);
        if msb != 0 {
            let shift = (8 - bits) as u32;
            let val = (byte >> shift) as libc::c_ulong;
            w(b, val, bits as libc::c_int);
        } else {
            let val = byte as libc::c_ulong;
            w(b, val, bits as libc::c_int);
        }
    }
}
