use libc::{c_int, free};
pub unsafe fn ogg_sync_destroy(oy: *mut ogg_sync_state) -> c_int {
    if !oy.is_null() {
        ogg_sync_clear(oy);
        free(oy as *mut libc::c_void);
    }
    0
}
