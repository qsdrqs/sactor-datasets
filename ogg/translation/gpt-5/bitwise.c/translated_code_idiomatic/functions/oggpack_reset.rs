pub fn oggpack_reset(b: &mut OggPackBuffer<'_>) {
    if b.buffer.is_empty() {
        return;
    }
    b.ptr = 0;
    b.buffer[0] = 0;
    b.endbyte = 0;
    b.endbit = b.endbyte as i32;
}
