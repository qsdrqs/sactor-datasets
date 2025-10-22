pub fn oggpack_look1(b: &OggPackBuffer<'_>) -> i64 {
    if b.endbyte >= b.storage {
        return -1;
    }
    let byte = match b.buffer.get(b.ptr) {
        Some(&v) => v,
        None => return -1,
    };
    let shift = b.endbit as u32;
    match byte.checked_shr(shift) {
        Some(v) => (v & 1) as i64,
        None => -1,
    }
}
