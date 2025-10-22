pub unsafe fn oggpackB_look(b: *mut oggpack_buffer, mut bits: libc::c_int) -> libc::c_long {
    let m: libc::c_int = 32 - bits;
    if m < 0 || m > 32 {
        return -1;
    }
    bits += (*b).endbit;
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).endbyte > (*b).storage - (((bits + 7) >> 3) as libc::c_long) {
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    let p = (*b).ptr as *const libc::c_uchar;
    let mut ret: libc::c_ulong =
        ((*p.offset(0) as libc::c_ulong) << ((24 + (*b).endbit) as u32)) as libc::c_ulong;
    if bits > 8 {
        ret |= ((*p.offset(1) as libc::c_ulong) << ((16 + (*b).endbit) as u32)) as libc::c_ulong;
        if bits > 16 {
            ret |= ((*p.offset(2) as libc::c_ulong) << ((8 + (*b).endbit) as u32)) as libc::c_ulong;
            if bits > 24 {
                ret |= ((*p.offset(3) as libc::c_ulong) << ((*b).endbit as u32)) as libc::c_ulong;
                if bits > 32 && (*b).endbit != 0 {
                    ret |= ((*p.offset(4) as libc::c_ulong) >> ((8 - (*b).endbit) as u32))
                        as libc::c_ulong;
                }
            }
        }
    }
    let mask: libc::c_ulong = 0xffffffffu64 as libc::c_ulong;
    let ret32 = ret & mask;
    let sh1: u32 = (m >> 1) as u32;
    let sh2: u32 = ((m + 1) >> 1) as u32;
    ((ret32 >> sh1) >> sh2) as libc::c_long
}
