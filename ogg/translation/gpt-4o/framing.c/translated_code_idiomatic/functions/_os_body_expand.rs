pub fn _os_body_expand(os: &mut OggStreamState, needed: i64) -> i32 {
    const LONG_MAX: i64 = i64::MAX;
    if os.body_storage - needed <= os.body_fill {
        let mut body_storage: i64;
        if os.body_storage > LONG_MAX - needed {
            ogg_stream_clear(Some(os));
            return -1;
        }
        body_storage = os.body_storage + needed;
        if body_storage < LONG_MAX - 1024 {
            body_storage += 1024;
        }
        let mut new_body_data = Vec::with_capacity(body_storage as usize);
        new_body_data.extend_from_slice(os.body_data);
        new_body_data.resize(body_storage as usize, 0);
        if new_body_data.len() < body_storage as usize {
            ogg_stream_clear(Some(os));
            return -1;
        }
        os.body_storage = body_storage;
        fn update_body_data<'a>(os: &mut OggStreamState<'a>, new_data: Vec<u8>) {
            os.body_data = Box::leak(new_data.into_boxed_slice());
        }
        update_body_data(os, new_body_data);
    }
    0
}
