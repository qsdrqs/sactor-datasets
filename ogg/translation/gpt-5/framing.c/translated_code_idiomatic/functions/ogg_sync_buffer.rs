pub fn ogg_sync_buffer<'a, 'b>(oy: &'b mut OggSyncState<'a>, size: usize) -> Option<&'b mut [u8]> {
    if ogg_sync_check(oy) != 0 {
        return None;
    }
    oy.storage = oy.data.len();
    if oy.fill > oy.storage {
        oy.fill = oy.storage;
    }
    if oy.returned > oy.fill {
        oy.returned = oy.fill;
    }
    if oy.returned != 0 {
        let returned = oy.returned;
        let fill = oy.fill;
        if returned < fill {
            oy.data.copy_within(returned..fill, 0);
            oy.fill = fill - returned;
        } else {
            oy.fill = 0;
        }
        oy.returned = 0;
    }
    let available = oy.storage.saturating_sub(oy.fill);
    if size > available {
        let max_total = i32::MAX as usize;
        if oy.fill > max_total.saturating_sub(4096) {
            let _ = ogg_sync_clear(Some(oy));
            return None;
        }
        let max_request = max_total - 4096 - oy.fill;
        if size > max_request {
            let _ = ogg_sync_clear(Some(oy));
            return None;
        }
        let newsize = oy.fill.saturating_add(size).saturating_add(4096);
        let mut new_buf = Vec::<u8>::new();
        if new_buf.try_reserve_exact(newsize).is_err() {
            let _ = ogg_sync_clear(Some(oy));
            return None;
        }
        new_buf.resize(newsize, 0);
        if oy.fill > 0 {
            new_buf[..oy.fill].copy_from_slice(&oy.data[..oy.fill]);
        }
        let boxed = new_buf.into_boxed_slice();
        let leaked: &'static mut [u8] = Box::leak(boxed);
        oy.data = leaked;
        oy.storage = newsize;
    }
    if size > oy.storage.saturating_sub(oy.fill) {
        return None;
    }
    let start = oy.fill;
    let end = start + size;
    Some(&mut oy.data[start..end])
}
