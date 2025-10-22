use libc::{c_int, c_long, realloc};
use std::i64;
pub unsafe fn _os_lacing_expand(os: *mut ogg_stream_state, needed: c_long) -> c_int {
    if (*os).lacing_storage - needed <= (*os).lacing_fill {
        let mut lacing_storage: c_long;
        let mut ret: *mut libc::c_void;
        if (*os).lacing_storage > i64::MAX - needed {
            ogg_stream_clear(os);
            return -1;
        }
        lacing_storage = (*os).lacing_storage + needed;
        if lacing_storage < i64::MAX - 32 {
            lacing_storage += 32;
        }
        ret = realloc(
            (*os).lacing_vals as *mut libc::c_void,
            lacing_storage as usize * std::mem::size_of::<libc::c_int>(),
        );
        if ret.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).lacing_vals = ret as *mut libc::c_int;
        ret = realloc(
            (*os).granule_vals as *mut libc::c_void,
            lacing_storage as usize * std::mem::size_of::<libc::c_long>(),
        );
        if ret.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).granule_vals = ret as *mut libc::c_long;
        (*os).lacing_storage = lacing_storage;
    }
    0
}
