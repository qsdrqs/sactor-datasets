pub unsafe fn oggpack_write(
    b: *mut oggpack_buffer,
    mut value: libc::c_ulong,
    mut bits: libc::c_int,
) {
    if bits < 0 || bits > 32 {
        oggpack_writeclear(b);
        return;
    }
    if (*b).endbyte >= (*b).storage - 4 {
        let mut ret: *mut libc::c_void;
        if (*b).ptr.is_null() {
            return;
        }
        if (*b).storage > libc::c_long::MAX - 256 as libc::c_long {
            oggpack_writeclear(b);
            return;
        }
        ret = libc::realloc(
            (*b).buffer as *mut libc::c_void,
            ((*b).storage + 256) as libc::size_t,
        );
        if ret.is_null() {
            oggpack_writeclear(b);
            return;
        }
        (*b).buffer = ret as *mut libc::c_uchar;
        (*b).storage += 256;
        (*b).ptr = (*b).buffer.offset((*b).endbyte as isize);
    }
    value &= mask[bits as usize];
    bits += (*b).endbit;
    let endbit_u32 = (*b).endbit as u32;
    let p0 = *(*b).ptr.add(0);
    *(*b).ptr.add(0) = p0 | ((value << endbit_u32) as libc::c_uchar);
    if bits >= 8 {
        *(*b).ptr.add(1) = (value >> (8 - endbit_u32)) as libc::c_uchar;
        if bits >= 16 {
            *(*b).ptr.add(2) = (value >> (16 - endbit_u32)) as libc::c_uchar;
            if bits >= 24 {
                *(*b).ptr.add(3) = (value >> (24 - endbit_u32)) as libc::c_uchar;
                if bits >= 32 {
                    if (*b).endbit != 0 {
                        *(*b).ptr.add(4) = (value >> (32 - endbit_u32)) as libc::c_uchar;
                    } else {
                        *(*b).ptr.add(4) = 0;
                    }
                }
            }
        }
    }
    (*b).endbyte += (bits / 8) as libc::c_long;
    (*b).ptr = (*b).ptr.add((bits / 8) as usize);
    (*b).endbit = (bits & 7) as libc::c_int;
}
