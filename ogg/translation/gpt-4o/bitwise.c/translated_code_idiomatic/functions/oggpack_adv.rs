pub fn oggpack_adv(b: &mut OggpackBuffer, bits: i32) {
    let mut bits = bits + b.endbit;
    let storage_bytes = b.storage as usize;
    let mut ptr_guard = b.ptr.lock().unwrap();
    let ptr_len = ptr_guard.len();
    if b.endbyte > b.storage - (((bits + 7) >> 3) as i64) {
        ptr_guard.clear();
        b.endbyte = b.storage;
        b.endbit = 1;
        return;
    }
    let byte_offset = (bits / 8) as usize;
    if byte_offset < ptr_len {
        ptr_guard.drain(..byte_offset);
    } else {
        ptr_guard.clear();
    }
    b.endbyte += byte_offset as i64;
    b.endbit = bits & 7;
}
