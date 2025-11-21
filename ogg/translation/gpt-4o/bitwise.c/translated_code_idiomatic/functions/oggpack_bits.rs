pub fn oggpack_bits(b: &OggpackBuffer) -> i64 {
    b.endbyte * 8 + b.endbit as i64
}
