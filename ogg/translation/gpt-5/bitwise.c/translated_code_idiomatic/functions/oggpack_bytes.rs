pub fn oggpack_bytes(b: &OggPackBuffer<'_>) -> usize {
    debug_assert!((0..=7).contains(&b.endbit), "endbit should be in 0..=7");
    b.endbyte + ((b.endbit + 7) / 8) as usize
}
