pub fn oggpack_writecheck(b: &OggpackBuffer) -> i32 {
    if b.storage == 0 {
        return -1;
    }
    0
}
