pub fn oggpack_writecheck(b: &OggPackBuffer<'_>) -> i32 {
    if b.storage == 0 || b.buffer.is_empty() {
        -1
    } else {
        0
    }
}
