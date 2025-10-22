pub unsafe fn ogg_sync_reset(oy: *mut ogg_sync_state) -> libc::c_int {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    (*oy).fill = 0;
    (*oy).returned = 0;
    (*oy).unsynced = 0;
    (*oy).headerbytes = 0;
    (*oy).bodybytes = 0;
    0
}
