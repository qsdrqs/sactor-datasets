pub unsafe fn oggpackB_read(b: *mut oggpack_buffer, mut bits: libc::c_int) -> libc::c_long {
    let m_i32: libc::c_int = 32 - bits;
    if m_i32 < 0 || m_i32 > 32 {
        (*b).ptr = core::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
        return -1 as libc::c_long;
    }
    bits += (*b).endbit;
    if (*b).endbyte + (4 as libc::c_long) >= (*b).storage {
        if (*b).endbyte > (*b).storage - (((bits + 7) >> 3) as libc::c_long) {
            (*b).ptr = core::ptr::null_mut();
            (*b).endbyte = (*b).storage;
            (*b).endbit = 1;
            return -1 as libc::c_long;
        } else if bits == 0 {
            return 0 as libc::c_long;
        }
    }
    let p = (*b).ptr;
    let mut ret_u: u64 = (*p.add(0) as u64) << (24u32 + (*b).endbit as u32);
    if bits > 8 {
        ret_u |= (*p.add(1) as u64) << (16u32 + (*b).endbit as u32);
        if bits > 16 {
            ret_u |= (*p.add(2) as u64) << (8u32 + (*b).endbit as u32);
            if bits > 24 {
                ret_u |= (*p.add(3) as u64) << ((*b).endbit as u32);
                if bits > 32 && (*b).endbit != 0 {
                    ret_u |= (*p.add(4) as u64) >> (8u32 - (*b).endbit as u32);
                }
            }
        }
    }
    let m_u32 = m_i32 as u32;
    ret_u = ((ret_u & 0xffffffffu64) >> (m_u32 >> 1)) >> ((m_u32 + 1) >> 1);
    let advance_bytes = (bits >> 3) as libc::c_long;
    (*b).ptr = (*b).ptr.add(advance_bytes as usize);
    (*b).endbyte += advance_bytes;
    (*b).endbit = (bits & 7) as libc::c_int;
    ret_u as libc::c_long
}
