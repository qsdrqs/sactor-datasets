pub fn oggpack_writeinit(b: &mut OggPackBuffer<'static>) {
    const DEFAULT_STORAGE: usize = 256;
    let buf: &'static mut [u8] = Box::leak(vec![0u8; DEFAULT_STORAGE].into_boxed_slice());
    b.endbyte = 0;
    b.endbit = 0;
    b.buffer = buf;
    b.ptr = 0;
    b.storage = DEFAULT_STORAGE;
    if !b.buffer.is_empty() {
        b.buffer[0] = 0;
    }
}
