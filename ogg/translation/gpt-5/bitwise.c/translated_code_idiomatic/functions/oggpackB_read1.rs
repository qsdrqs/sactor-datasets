pub fn oggpackB_read1(b: &mut OggPackBuffer<'_>) -> i32 {
    let storage = b.storage.min(b.buffer.len());
    if b.endbyte >= storage {
        b.ptr = storage;
        b.endbyte = storage;
        b.endbit = 1;
        return -1;
    }
    let byte = b.buffer[b.endbyte];
    let shift = (7 - b.endbit) as u32;
    let ret = ((byte as i32 >> shift) & 1) as i32;
    b.endbit += 1;
    if b.endbit > 7 {
        b.endbit = 0;
        b.endbyte += 1;
        b.ptr = b.endbyte;
    }
    ret
}
