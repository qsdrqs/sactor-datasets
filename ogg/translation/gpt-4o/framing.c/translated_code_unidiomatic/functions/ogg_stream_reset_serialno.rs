pub unsafe fn ogg_stream_reset_serialno(
    os: *mut ogg_stream_state,
    serialno: libc::c_int,
) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    ogg_stream_reset(os);
    (*os).serialno = serialno as libc::c_long;
    0
}
