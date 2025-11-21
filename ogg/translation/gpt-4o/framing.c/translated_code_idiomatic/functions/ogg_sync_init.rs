pub fn ogg_sync_init(oy: &mut OggSyncState) -> i32 {
    if !oy.data.is_empty() {
        oy.storage = -1;
        oy.data.iter_mut().for_each(|x| *x = 0);
    }
    0
}
