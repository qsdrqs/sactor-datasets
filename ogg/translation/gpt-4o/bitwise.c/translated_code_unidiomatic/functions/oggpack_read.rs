use libc::{c_int, c_long, c_uchar};
pub unsafe fn oggpack_read(b: *mut oggpack_buffer, bits: c_int) -> c_long {
    let mut ret: c_long;
    let m: u32;
    if bits < 0 || bits > 32 {
        goto_err(b);
        return -1;
    }
    m = mask[bits as usize];
    let bits = bits + (*b).endbit;
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).endbyte > (*b).storage - (((bits + 7) as c_long) >> 3) {
            goto_err(b);
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    ret = (*(*b).ptr.offset(0) as c_long) >> (*b).endbit;
    if bits > 8 {
        ret |= ((*(*b).ptr.offset(1) as c_long) << (8 - (*b).endbit)) as c_long;
        if bits > 16 {
            ret |= ((*(*b).ptr.offset(2) as c_long) << (16 - (*b).endbit)) as c_long;
            if bits > 24 {
                ret |= ((*(*b).ptr.offset(3) as c_long) << (24 - (*b).endbit)) as c_long;
                if bits > 32 && (*b).endbit != 0 {
                    ret |= ((*(*b).ptr.offset(4) as c_long) << (32 - (*b).endbit)) as c_long;
                }
            }
        }
    }
    ret &= m as c_long;
    (*b).ptr = (*b).ptr.offset((bits / 8) as isize);
    (*b).endbyte += (bits / 8) as c_long;
    (*b).endbit = bits & 7;
    return ret;
    unsafe fn goto_err(b: *mut oggpack_buffer) {
        (*b).ptr = std::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
    }
}
