#[no_mangle]
pub unsafe fn ogg_stream_pageout(os: *mut ogg_stream_state, og: *mut ogg_page) -> libc::c_int {
    let mut force: libc::c_int = 0;
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    if ((*os).e_o_s != 0 && (*os).lacing_fill != 0) || ((*os).lacing_fill != 0 && (*os).b_o_s == 0)
    {
        force = 1;
    }
    ogg_stream_flush_i(os, og, force, 4096 as libc::c_int)
}
