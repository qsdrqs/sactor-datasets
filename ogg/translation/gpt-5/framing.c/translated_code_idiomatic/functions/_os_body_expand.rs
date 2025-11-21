pub fn _os_body_expand<'a>(os: &mut OggStreamState<'a>, needed: isize) -> i32 {
    if needed <= 0 {
        return 0;
    }
    let needed_usize = match usize::try_from(needed) {
        Ok(v) => v,
        Err(_) => {
            ogg_stream_clear(os);
            return -1;
        }
    };
    let need_expand = match os.body_fill.checked_add(needed_usize) {
        Some(sum) => os.body_storage <= sum,
        None => true,
    };
    if !need_expand {
        return 0;
    }
    let base = match os.body_storage.checked_add(needed_usize) {
        Some(v) => v,
        None => {
            ogg_stream_clear(os);
            return -1;
        }
    };
    let new_storage = if base < usize::MAX.saturating_sub(1024) {
        base + 1024
    } else {
        base
    };
    let mut new_buf: Vec<u8> = Vec::new();
    if new_buf.try_reserve_exact(new_storage).is_err() {
        ogg_stream_clear(os);
        return -1;
    }
    new_buf.resize(new_storage, 0);
    let to_copy = core::cmp::min(os.body_fill, os.body_data.len());
    new_buf[..to_copy].copy_from_slice(&os.body_data[..to_copy]);
    let leaked_slice: &'static mut [u8] = Box::leak(new_buf.into_boxed_slice());
    os.body_data = leaked_slice;
    os.body_storage = new_storage;
    0
}
