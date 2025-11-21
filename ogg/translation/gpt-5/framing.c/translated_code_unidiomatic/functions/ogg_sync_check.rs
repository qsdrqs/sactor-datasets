pub unsafe fn ogg_sync_check(oy: *mut ogg_sync_state) -> libc::c_int {
    if (*oy).storage < 0 {
        -1 as libc::c_int
    } else {
        0 as libc::c_int
    }
}
