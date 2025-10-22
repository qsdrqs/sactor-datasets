pub fn ogg_sync_clear<'a>(oy: Option<&mut OggSyncState<'a>>) -> i32 {
    if let Some(state) = oy {
        state.storage = 0;
        state.fill = 0;
        state.returned = 0;
        state.unsynced = false;
        state.headerbytes = 0;
        state.bodybytes = 0;
    }
    0
}
