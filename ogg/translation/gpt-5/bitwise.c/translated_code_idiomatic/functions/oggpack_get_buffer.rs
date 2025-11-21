pub fn oggpack_get_buffer<'a>(b: &'a mut OggPackBuffer<'a>) -> &'a mut [u8] {
    &mut *b.buffer
}
