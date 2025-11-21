pub fn _os_lacing_expand<'a>(os: &mut OggStreamState<'a>, needed: usize) -> i32 {
    let available = os.lacing_storage.saturating_sub(os.lacing_fill);
    if available <= needed {
        let mut new_storage = match os.lacing_storage.checked_add(needed) {
            Some(v) => v,
            None => {
                ogg_stream_clear(os);
                return -1;
            }
        };
        if let Some(v) = new_storage.checked_add(32) {
            new_storage = v;
        }
        let old_lacing_len = os.lacing_vals.len();
        let old_granule_len = os.granule_vals.len();
        let mut new_lacing = vec![0i32; new_storage].into_boxed_slice();
        let mut new_granule = vec![0i64; new_storage].into_boxed_slice();
        let copy_lacing_len = old_lacing_len.min(new_storage);
        let copy_granule_len = old_granule_len.min(new_storage);
        new_lacing[..copy_lacing_len].copy_from_slice(&os.lacing_vals[..copy_lacing_len]);
        new_granule[..copy_granule_len].copy_from_slice(&os.granule_vals[..copy_granule_len]);
        os.lacing_vals = Box::leak(new_lacing);
        os.granule_vals = Box::leak(new_granule);
        os.lacing_storage = new_storage;
    }
    0
}
