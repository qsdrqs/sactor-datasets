pub fn oggpack_read1(b: &mut OggPackBuffer<'_>) -> Option<u8> {
    let storage = b.storage.min(b.buffer.len());
    if b.endbyte >= storage {
        b.ptr = storage;
        b.endbyte = storage;
        b.endbit = 1;
        return None;
    }
    let byte = *b.buffer.get(b.endbyte)?;
    let bit = ((byte as u32) >> (b.endbit as u32)) & 1;
    b.endbit += 1;
    if b.endbit > 7 {
        b.endbit = 0;
        b.endbyte = (b.endbyte + 1).min(storage);
    }
    b.ptr = b.endbyte;
    Some(bit as u8)
}
