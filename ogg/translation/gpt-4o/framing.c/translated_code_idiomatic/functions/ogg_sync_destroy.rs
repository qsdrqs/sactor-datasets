pub fn ogg_sync_destroy(oy: Option<Box<OggSyncState>>) -> i32 {
    if let Some(mut oy_box) = oy {
        ogg_sync_clear(&mut oy_box);
    }
    0
}
