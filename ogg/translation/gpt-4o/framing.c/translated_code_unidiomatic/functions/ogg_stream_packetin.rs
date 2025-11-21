use libc::{c_int, c_long, c_void, size_t};
pub unsafe fn ogg_stream_packetin(os: *mut ogg_stream_state, op: *mut ogg_packet) -> c_int {
    let mut iov = ogg_iovec_t {
        iov_base: (*op).packet as *mut c_void,
        iov_len: (*op).bytes as size_t,
    };
    ogg_stream_iovecin(os, &mut iov, 1, (*op).e_o_s, (*op).granulepos)
}
