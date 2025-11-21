pub fn ogg_sync_init<'a>(buffer: &'a mut [u8]) -> OggSyncState<'a> {
    OggSyncState {
        data: buffer,
        storage: 0,
        fill: 0,
        returned: 0,
        unsynced: false,
        headerbytes: 0,
        bodybytes: 0,
    }
}
