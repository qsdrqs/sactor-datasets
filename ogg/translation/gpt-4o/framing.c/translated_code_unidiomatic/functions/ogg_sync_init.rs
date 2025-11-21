use libc::{c_int, c_uchar, memset};
pub unsafe fn ogg_sync_init(oy: *mut ogg_sync_state) -> c_int {
    if !oy.is_null() {
        (*oy).storage = -1;
        memset(
            oy as *mut libc::c_void,
            0,
            std::mem::size_of::<ogg_sync_state>(),
        );
    }
    0
}
