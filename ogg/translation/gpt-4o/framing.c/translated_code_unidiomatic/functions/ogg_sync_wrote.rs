pub unsafe fn ogg_sync_wrote(oy: *mut ogg_sync_state, bytes: libc::c_long) -> libc::c_int {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    if (*oy).fill + bytes as libc::c_int > (*oy).storage {
        return -1;
    }
    (*oy).fill += bytes as libc::c_int;
    0
}
