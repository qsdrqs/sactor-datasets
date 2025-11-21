use libc::{c_char, c_int, c_long, c_void, malloc, memmove, realloc, INT_MAX};
pub unsafe fn ogg_sync_buffer(oy: *mut ogg_sync_state, size: c_long) -> *mut c_char {
    if ogg_sync_check(oy) != 0 {
        return std::ptr::null_mut();
    }
    if (*oy).returned != 0 {
        (*oy).fill -= (*oy).returned;
        if (*oy).fill > 0 {
            memmove(
                (*oy).data as *mut c_void,
                (*oy).data.add((*oy).returned as usize) as *const c_void,
                (*oy).fill as usize,
            );
        }
        (*oy).returned = 0;
    }
    if size > (*oy).storage as c_long - (*oy).fill as c_long {
        let mut newsize: c_long;
        let ret: *mut c_void;
        if size > (INT_MAX - 4096 - (*oy).fill) as c_long {
            ogg_sync_clear(oy);
            return std::ptr::null_mut();
        }
        newsize = size + (*oy).fill as c_long + 4096;
        if !(*oy).data.is_null() {
            ret = realloc((*oy).data as *mut c_void, newsize as usize);
        } else {
            ret = malloc(newsize as usize);
        }
        if ret.is_null() {
            ogg_sync_clear(oy);
            return std::ptr::null_mut();
        }
        (*oy).data = ret as *mut libc::c_uchar;
        (*oy).storage = newsize as c_int;
    }
    (*oy).data.add((*oy).fill as usize) as *mut c_char
}
