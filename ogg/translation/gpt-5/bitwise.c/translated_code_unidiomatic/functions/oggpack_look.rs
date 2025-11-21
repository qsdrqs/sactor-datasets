pub unsafe fn oggpack_look(b: *mut oggpack_buffer, bits: libc::c_int) -> libc::c_long {
    let mut bits_ = bits;
    if bits_ < 0 || bits_ > 32 {
        return -1 as libc::c_long;
    }
    let m: libc::c_ulong = mask[bits_ as usize];
    bits_ += (*b).endbit;
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).endbyte > (*b).storage - (((bits_ + 7) >> 3) as libc::c_long) {
            return -1 as libc::c_long;
        } else if bits_ == 0 {
            return 0 as libc::c_long;
        }
    }
    let ptr = (*b).ptr;
    let mut ret: libc::c_ulong = ((*ptr.add(0)) as libc::c_ulong) >> ((*b).endbit as u32);
    if bits_ > 8 {
        ret |= ((*ptr.add(1)) as libc::c_ulong) << ((8 - (*b).endbit) as u32);
        if bits_ > 16 {
            ret |= ((*ptr.add(2)) as libc::c_ulong) << ((16 - (*b).endbit) as u32);
            if bits_ > 24 {
                ret |= ((*ptr.add(3)) as libc::c_ulong) << ((24 - (*b).endbit) as u32);
                if bits_ > 32 && (*b).endbit != 0 {
                    ret |= ((*ptr.add(4)) as libc::c_ulong) << ((32 - (*b).endbit) as u32);
                }
            }
        }
    }
    (m & ret) as libc::c_long
}
