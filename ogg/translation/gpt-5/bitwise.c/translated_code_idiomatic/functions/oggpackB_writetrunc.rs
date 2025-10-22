pub fn oggpackB_writetrunc(b: &mut OggPackBuffer<'_>, mut bits: usize) {
    let bytes = bits >> 3;
    bits -= bytes * 8;
    b.ptr = bytes;
    b.endbit = bits as i32;
    b.endbyte = bytes;
    if let Some(byte) = b.buffer.get_mut(b.ptr) {
        let mask = MASK_8B[bits as usize];
        *byte &= mask;
    }
}
