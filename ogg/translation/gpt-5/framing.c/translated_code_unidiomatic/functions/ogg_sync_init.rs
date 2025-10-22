#[no_mangle]
pub fn ogg_sync_init(oy: *mut ogg_sync_state) -> libc::c_int {
    unsafe {
        if !oy.is_null() {
            (*oy).storage = -1;
            libc::memset(
                oy as *mut libc::c_void,
                0,
                core::mem::size_of::<ogg_sync_state>(),
            );
        }
    }
    0
}
