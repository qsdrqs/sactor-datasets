use libc::{c_int, c_long, c_uchar, realloc};
use std::i64;
pub unsafe fn oggpackB_write(b: *mut oggpack_buffer, mut value: u32, bits: c_int) {
    if bits < 0 || bits > 32 {
        oggpack_writeclear(b);
        return;
    }
    if (*b).endbyte >= (*b).storage - 4 {
        if (*b).ptr.is_null() {
            return;
        }
        if (*b).storage > i64::MAX - 256 {
            oggpack_writeclear(b);
            return;
        }
        let ret = realloc(
            (*b).buffer as *mut libc::c_void,
            ((*b).storage + 256) as usize,
        );
        if ret.is_null() {
            oggpack_writeclear(b);
            return;
        }
        (*b).buffer = ret as *mut c_uchar;
        (*b).storage += 256;
        (*b).ptr = (*b).buffer.offset((*b).endbyte as isize);
    }
    if bits > 0 {
        value = (value & mask[bits as usize]) << (32 - bits);
    }
    let mut total_bits = bits + (*b).endbit;
    *(*b).ptr.offset(0) |= (value >> (24 + (*b).endbit)) as c_uchar;
    if total_bits >= 8 {
        *(*b).ptr.offset(1) = (value >> (16 + (*b).endbit)) as c_uchar;
        if total_bits >= 16 {
            *(*b).ptr.offset(2) = (value >> (8 + (*b).endbit)) as c_uchar;
            if total_bits >= 24 {
                *(*b).ptr.offset(3) = (value >> (*b).endbit) as c_uchar;
                if total_bits >= 32 {
                    if (*b).endbit != 0 {
                        *(*b).ptr.offset(4) = (value << (8 - (*b).endbit)) as c_uchar;
                    } else {
                        *(*b).ptr.offset(4) = 0;
                    }
                }
            }
        }
    }
    (*b).endbyte += (total_bits / 8) as c_long;
    (*b).ptr = (*b).ptr.offset((total_bits / 8) as isize);
    (*b).endbit = total_bits & 7;
}
