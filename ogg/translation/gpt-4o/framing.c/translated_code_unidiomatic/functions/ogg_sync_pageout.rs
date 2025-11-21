use libc;
pub unsafe fn ogg_sync_pageout(oy: *mut ogg_sync_state, og: *mut ogg_page) -> libc::c_int {
    if ogg_sync_check(oy) != 0 {
        return 0;
    }
    loop {
        let ret = ogg_sync_pageseek(oy, og);
        if ret > 0 {
            return 1;
        }
        if ret == 0 {
            return 0;
        }
        if (*oy).unsynced == 0 {
            (*oy).unsynced = 1;
            return -1;
        }
    }
}
