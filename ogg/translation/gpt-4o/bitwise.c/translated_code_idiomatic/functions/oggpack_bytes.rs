pub fn oggpack_bytes(b: &OggpackBuffer) -> i64 {
    b.endbyte + ((b.endbit as i64) + 7) / 8
}
