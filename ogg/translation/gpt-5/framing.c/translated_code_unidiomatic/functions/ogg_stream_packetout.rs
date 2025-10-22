#[no_mangle]
pub unsafe fn ogg_stream_packetout(os: *mut ogg_stream_state, op: *mut ogg_packet) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        0
    } else {
        _packetout(os, op, 1 as libc::c_int)
    }
}
