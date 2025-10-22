use libc::{c_int, free};
pub unsafe fn ogg_stream_destroy(os: *mut ogg_stream_state) -> c_int {
    if !os.is_null() {
        ogg_stream_clear(os);
        free(os as *mut libc::c_void);
    }
    0
}
