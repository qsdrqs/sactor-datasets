pub fn oggpack_get_buffer(b: &OggpackBuffer) -> Arc<Mutex<Vec<u8>>> {
    Arc::clone(&b.buffer)
}
