pub unsafe fn oggpack_look(b: *mut oggpack_buffer, bits: libc::c_int) -> libc::c_long {
    if bits < 0 || bits > 32 {
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
