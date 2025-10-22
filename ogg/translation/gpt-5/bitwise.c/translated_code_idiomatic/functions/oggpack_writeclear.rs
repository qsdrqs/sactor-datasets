pub fn oggpack_writeclear(b: &mut OggPackBuffer<'_>) {
    b.buffer = &mut [];
    b.endbyte = 0;
    b.endbit = 0;
    b.ptr = 0;
    b.storage = 0;
}
