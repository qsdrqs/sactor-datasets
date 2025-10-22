pub unsafe fn _os_lacing_expand(os: *mut ogg_stream_state, needed: libc::c_long) -> libc::c_int {
    if (*os).lacing_storage.wrapping_sub(needed) <= (*os).lacing_fill {
        let mut lacing_storage = match (*os).lacing_storage.checked_add(needed) {
            Some(v) => v,
            None => {
                ogg_stream_clear(os);
                return -1;
            }
        };
        if let Some(v) = lacing_storage.checked_add(32) {
            lacing_storage = v;
        }
        let bytes_lacing = (lacing_storage as libc::size_t)
            .wrapping_mul(core::mem::size_of::<libc::c_int>() as libc::size_t);
        let ret1 = libc::realloc((*os).lacing_vals as *mut libc::c_void, bytes_lacing);
        if ret1.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).lacing_vals = ret1 as *mut libc::c_int;
        let bytes_granule = (lacing_storage as libc::size_t)
            .wrapping_mul(core::mem::size_of::<libc::c_long>() as libc::size_t);
        let ret2 = libc::realloc((*os).granule_vals as *mut libc::c_void, bytes_granule);
        if ret2.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).granule_vals = ret2 as *mut libc::c_long;
        (*os).lacing_storage = lacing_storage;
    }
    0
}
