pub fn ogg_sync_wrote(oy: &mut OggSyncState<'_>, bytes: isize) -> i32 {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    if bytes >= 0 {
        let b = bytes as usize;
        if b > oy.storage.saturating_sub(oy.fill) {
            return -1;
        }
        oy.fill += b;
    } else {
        let b = (-bytes) as usize;
        if b > oy.fill {
            return -1;
        }
        oy.fill -= b;
    }
    0
}
