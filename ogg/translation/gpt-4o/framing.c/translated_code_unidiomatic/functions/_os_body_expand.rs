pub unsafe fn _os_body_expand(os: *mut ogg_stream_state, needed: libc::c_long) -> libc::c_int {
    const LONG_MAX: libc::c_long = libc::c_long::MAX;
    if (*os).body_storage - needed <= (*os).body_fill {
        let mut body_storage: libc::c_long;
        let ret: *mut libc::c_void;
        if (*os).body_storage > LONG_MAX - needed {
            ogg_stream_clear(os);
            return -1;
        }
        body_storage = (*os).body_storage + needed;
        if body_storage < LONG_MAX - 1024 {
            body_storage += 1024;
        }
        ret = libc::realloc(
            (*os).body_data as *mut libc::c_void,
            (body_storage as usize) * std::mem::size_of::<libc::c_uchar>(),
        );
        if ret.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).body_storage = body_storage;
        (*os).body_data = ret as *mut libc::c_uchar;
    }
    0
}
