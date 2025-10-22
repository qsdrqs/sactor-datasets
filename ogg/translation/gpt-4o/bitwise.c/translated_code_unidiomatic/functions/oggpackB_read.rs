pub unsafe fn oggpackB_read(b: *mut oggpack_buffer, bits: libc::c_int) -> libc::c_long {
    let mut ret: libc::c_long;
    let m = 32 - bits;
    if m < 0 || m > 32 {
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
