pub unsafe fn ogg_stream_check(os: *mut ogg_stream_state) -> libc::c_int {
    if os.is_null() || (*os).body_data.is_null() {
        return -1 as libc::c_int;
    }
    0 as libc::c_int
}
