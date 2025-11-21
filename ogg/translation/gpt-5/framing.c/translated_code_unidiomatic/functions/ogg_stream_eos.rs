#[no_mangle]
pub unsafe fn ogg_stream_eos(os: *mut ogg_stream_state) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return 1;
    }
    (*os).e_o_s
}
