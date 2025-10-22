pub unsafe fn ogg_stream_reset(os: *mut ogg_stream_state) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return -1 as libc::c_int;
    }
    (*os).body_fill = 0 as libc::c_long;
    (*os).body_returned = 0 as libc::c_long;
    (*os).lacing_fill = 0 as libc::c_long;
    (*os).lacing_packet = 0 as libc::c_long;
    (*os).lacing_returned = 0 as libc::c_long;
    (*os).header_fill = 0 as libc::c_int;
    (*os).e_o_s = 0 as libc::c_int;
    (*os).b_o_s = 0 as libc::c_int;
    (*os).pageno = -1 as libc::c_long;
    (*os).packetno = 0 as libc::c_long;
    (*os).granulepos = 0 as libc::c_long;
    0 as libc::c_int
}
