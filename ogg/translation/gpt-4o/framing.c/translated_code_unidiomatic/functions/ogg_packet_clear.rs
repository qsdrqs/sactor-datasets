use libc::{c_void, free, memset};
pub unsafe fn ogg_packet_clear(op: *mut ogg_packet) {
    if !(*op).packet.is_null() {
        free((*op).packet as *mut c_void);
    }
    memset(op as *mut c_void, 0, std::mem::size_of::<ogg_packet>());
}
