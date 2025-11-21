pub fn oggpackB_get_buffer(b: &OggpackBuffer) -> Arc<Mutex<Vec<u8>>> {
    oggpack_get_buffer(b)
}
