use libc::{c_int, c_void, free, memset};
pub unsafe fn ogg_sync_clear(oy: *mut ogg_sync_state) -> c_int {
    if !oy.is_null() {
        if !(*oy).data.is_null() {
            free((*oy).data as *mut c_void);
        }
        memset(oy as *mut c_void, 0, std::mem::size_of::<ogg_sync_state>());
    }
    0
}
