pub unsafe fn oggpackB_write(b: *mut oggpack_buffer, value: libc::c_ulong, mut bits: libc::c_int) {
    if b.is_null() {
        return;
    }
    if bits < 0 || bits > 32 {
        oggpack_writeclear(b);
        return;
    }
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).ptr.is_null() {
            return;
        }
        let long_max: libc::c_long =
            if core::mem::size_of::<libc::c_long>() == core::mem::size_of::<i64>() {
                i64::MAX as libc::c_long
            } else {
                i32::MAX as libc::c_long
            };
        if (*b).storage > long_max - 256 {
            oggpack_writeclear(b);
            return;
        }
        let new_size = ((*b).storage + 256) as libc::size_t;
        let ret = libc::realloc((*b).buffer as *mut libc::c_void, new_size);
        if ret.is_null() {
            oggpack_writeclear(b);
            return;
        }
        (*b).buffer = ret as *mut libc::c_uchar;
        (*b).storage += 256;
        (*b).ptr = (*b).buffer.offset((*b).endbyte as isize);
    }
    let val: u64 = ((value & mask[bits as usize]) as u64) << ((32 - bits) as u32);
    let endbit = (*b).endbit;
    bits += endbit;
    let p = (*b).ptr;
    let s0 = (24 + endbit) as u32;
    *p.add(0) |= (val >> s0) as libc::c_uchar;
    if bits >= 8 {
        let s1 = (16 + endbit) as u32;
        *p.add(1) = (val >> s1) as libc::c_uchar;
        if bits >= 16 {
            let s2 = (8 + endbit) as u32;
            *p.add(2) = (val >> s2) as libc::c_uchar;
            if bits >= 24 {
                let s3 = endbit as u32;
                *p.add(3) = (val >> s3) as libc::c_uchar;
                if bits >= 32 {
                    if endbit != 0 {
                        let s4 = (8 - endbit) as u32;
                        *p.add(4) = (val << s4) as libc::c_uchar;
                    } else {
                        *p.add(4) = 0;
                    }
                }
            }
        }
    }
    let nbytes = (bits / 8) as libc::c_long;
    (*b).endbyte += nbytes;
    (*b).ptr = (*b).ptr.add(nbytes as usize);
    (*b).endbit = bits & 7;
}
