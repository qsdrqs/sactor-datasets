pub fn ogg_sync_clear(oy: &mut OggSyncState) -> i32 {
    oy.data.fill(0);
    oy.storage = 0;
    oy.fill = 0;
    oy.returned = 0;
    oy.unsynced = 0;
    oy.headerbytes = 0;
    oy.bodybytes = 0;
    0
}
