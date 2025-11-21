use libc;
pub unsafe fn ogg_stream_flush_fill(
    os: *mut ogg_stream_state,
    og: *mut ogg_page,
    nfill: libc::c_int,
) -> libc::c_int {
    ogg_stream_flush_i(os, og, 1, nfill)
}
