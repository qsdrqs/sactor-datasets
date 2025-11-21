pub unsafe fn ogg_packet_clear(op: *mut ogg_packet) {
    libc::free((*op).packet as *mut libc::c_void);
    libc::memset(
        op as *mut libc::c_void,
        0,
        core::mem::size_of::<ogg_packet>(),
    );
}
