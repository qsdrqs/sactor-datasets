pub fn oggpack_writetrunc(b: &mut OggPackBuffer<'_>, bits: usize) {
    let bytes = bits >> 3;
    let rem_bits = (bits & 7) as i32;
    b.ptr = bytes;
    b.endbyte = bytes;
    b.endbit = rem_bits;
    if b.ptr < b.buffer.len() {
        let m = MASK[rem_bits as usize] as u8;
        b.buffer[b.ptr] &= m;
    }
}
