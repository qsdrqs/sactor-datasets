pub unsafe fn oggpack_read(b: *mut oggpack_buffer, mut bits: libc::c_int) -> libc::c_long {
    unsafe fn fail(b: *mut oggpack_buffer) -> libc::c_long {
        (*b).ptr = core::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1 as libc::c_int;
        -1 as libc::c_long
    }
    if bits < 0 || bits > 32 {
        return fail(b);
    }
    let m: libc::c_ulong = mask[bits as usize];
    bits += (*b).endbit;
    if (*b).endbyte >= (*b).storage - 4 as libc::c_long {
        if (*b).endbyte > (*b).storage - (((bits + 7) >> 3) as libc::c_long) {
            return fail(b);
        } else if bits == 0 {
            return 0 as libc::c_long;
        }
    }
    let p = (*b).ptr;
    let endbit = (*b).endbit;
    let mut ret_u: libc::c_ulong = (*p.add(0) as libc::c_ulong) >> (endbit as u32);
    if bits > 8 {
        let sh1 = (8 - endbit) as u32;
        ret_u |= ((*p.add(1)) as libc::c_ulong) << sh1;
        if bits > 16 {
            let sh2 = (16 - endbit) as u32;
            ret_u |= ((*p.add(2)) as libc::c_ulong) << sh2;
            if bits > 24 {
                let sh3 = (24 - endbit) as u32;
                ret_u |= ((*p.add(3)) as libc::c_ulong) << sh3;
                if bits > 32 && endbit != 0 {
                    let sh4 = (32 - endbit) as u32;
                    ret_u |= ((*p.add(4)) as libc::c_ulong) << sh4;
                }
            }
        }
    }
    ret_u &= m;
    let byte_advance = (bits / 8) as usize;
    (*b).ptr = (*b).ptr.add(byte_advance);
    (*b).endbyte += (bits / 8) as libc::c_long;
    (*b).endbit = (bits & 7) as libc::c_int;
    ret_u as libc::c_long
}
