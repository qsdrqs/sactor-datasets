pub unsafe fn ogg_stream_packetpeek(os: *mut ogg_stream_state, op: *mut ogg_packet) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    _packetout(os, op, 0)
}
