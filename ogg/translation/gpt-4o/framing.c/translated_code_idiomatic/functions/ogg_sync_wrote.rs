pub fn ogg_sync_wrote(oy: &mut OggSyncState, bytes: i32) -> i32 {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    if oy.fill + bytes > oy.storage {
        return -1;
    }
    oy.fill += bytes;
    0
}
