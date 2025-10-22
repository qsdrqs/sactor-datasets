pub fn oggpack_writeclear(b: &mut OggpackBuffer) {
    if !b.buffer.lock().unwrap().is_empty() {
        b.buffer.lock().unwrap().clear();
    }
    b.endbyte = 0;
    b.endbit = 0;
    b.ptr.lock().unwrap().clear();
    b.storage = 0;
}
