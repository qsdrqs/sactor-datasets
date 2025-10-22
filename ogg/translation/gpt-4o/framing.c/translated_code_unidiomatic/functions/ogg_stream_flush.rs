use libc;
pub unsafe fn ogg_stream_flush(os: *mut ogg_stream_state, og: *mut ogg_page) -> libc::c_int {
    ogg_stream_flush_i(os, og, 1, 4096)
}
