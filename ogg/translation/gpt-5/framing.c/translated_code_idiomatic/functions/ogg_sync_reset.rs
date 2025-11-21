pub fn ogg_sync_reset(oy: &mut OggSyncState<'_>) -> i32 {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    oy.fill = 0;
    oy.returned = 0;
    oy.unsynced = false;
    oy.headerbytes = 0;
    oy.bodybytes = 0;
    0
}
