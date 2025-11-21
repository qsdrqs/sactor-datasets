pub fn ogg_stream_destroy(os: *mut ogg_stream_state) -> libc::c_int {
    unsafe {
        if !os.is_null() {
            ogg_stream_clear(os);
            libc::free(os as *mut libc::c_void);
        }
    }
    0 as libc::c_int
}
