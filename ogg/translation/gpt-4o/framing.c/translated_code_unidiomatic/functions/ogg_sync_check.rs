use libc;
pub unsafe fn ogg_sync_check(oy: *mut ogg_sync_state) -> libc::c_int {
    if (*oy).storage < 0 {
        return -1;
    }
    0
}
