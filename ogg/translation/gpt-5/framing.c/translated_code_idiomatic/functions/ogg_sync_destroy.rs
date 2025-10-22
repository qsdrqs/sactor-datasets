pub fn ogg_sync_destroy<'a>(oy: Option<Box<OggSyncState<'a>>>) -> i32 {
    if let Some(mut oy_box) = oy {
        let _ = ogg_sync_clear(Some(&mut oy_box));
    }
    0
}
