pub fn ogg_sync_check(oy: &OggSyncState) -> i32 {
    if oy.storage < 0 {
        return -1;
    }
    0
}
