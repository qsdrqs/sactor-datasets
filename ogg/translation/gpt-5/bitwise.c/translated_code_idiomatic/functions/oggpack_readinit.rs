pub fn oggpack_readinit<'a>(buf: &'a mut [u8]) -> OggPackBuffer<'a> {
    let storage_len = buf.len();
    OggPackBuffer {
        endbyte: 0,
        endbit: 0,
        buffer: buf,
        ptr: 0,
        storage: storage_len,
    }
}
