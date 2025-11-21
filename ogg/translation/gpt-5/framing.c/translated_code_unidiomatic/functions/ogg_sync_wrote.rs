pub unsafe fn ogg_sync_wrote(oy: *mut ogg_sync_state, bytes: libc::c_long) -> libc::c_int {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    let oy_ref = &mut *oy;
    if (oy_ref.fill as libc::c_long + bytes) > oy_ref.storage as libc::c_long {
        return -1;
    }
    oy_ref.fill += bytes as libc::c_int;
    0
}
