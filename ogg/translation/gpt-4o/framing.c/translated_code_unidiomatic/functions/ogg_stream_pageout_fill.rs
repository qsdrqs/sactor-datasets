pub unsafe fn ogg_stream_pageout_fill(
    os: *mut ogg_stream_state,
    og: *mut ogg_page,
    nfill: libc::c_int,
) -> libc::c_int {
    let mut force = 0;
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    if ((*os).e_o_s != 0 && (*os).lacing_fill != 0) || ((*os).lacing_fill != 0 && (*os).b_o_s == 0)
    {
        force = 1;
    }
    ogg_stream_flush_i(os, og, force, nfill)
}
