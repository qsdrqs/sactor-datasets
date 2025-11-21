pub fn ogg_stream_packetin(os: *mut ogg_stream_state, op: *mut ogg_packet) -> libc::c_int {
    unsafe {
        let mut iov: ogg_iovec_t = ogg_iovec_t {
            iov_base: 0 as *mut libc::c_void,
            iov_len: 0 as libc::c_ulong,
        };
        iov.iov_base = (*op).packet as *mut libc::c_void;
        iov.iov_len = (*op).bytes as libc::c_ulong;
        ogg_stream_iovecin(
            os,
            &mut iov,
            1 as libc::c_int,
            (*op).e_o_s,
            (*op).granulepos,
        )
    }
}
