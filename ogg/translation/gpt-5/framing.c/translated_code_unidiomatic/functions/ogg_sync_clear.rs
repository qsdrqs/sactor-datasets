#[no_mangle]
pub unsafe fn ogg_sync_clear(oy: *mut ogg_sync_state) -> libc::c_int {
    if !oy.is_null() {
        let data_ptr = (*oy).data as *mut libc::c_void;
        if !data_ptr.is_null() {
            libc::free(data_ptr);
        }
        libc::memset(
            oy as *mut libc::c_void,
            0,
            core::mem::size_of::<ogg_sync_state>() as libc::size_t,
        );
    }
    0
}
