#[no_mangle]
pub unsafe fn ogg_sync_destroy(oy: *mut ogg_sync_state) -> libc::c_int {
    if !oy.is_null() {
        ogg_sync_clear(oy);
        libc::free(oy as *mut libc::c_void);
    }
    0
}
