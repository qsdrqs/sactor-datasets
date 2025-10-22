pub fn oggpack_bits(b: &OggPackBuffer<'_>) -> usize {
    b.endbyte.wrapping_mul(8).wrapping_add(b.endbit as usize)
}
