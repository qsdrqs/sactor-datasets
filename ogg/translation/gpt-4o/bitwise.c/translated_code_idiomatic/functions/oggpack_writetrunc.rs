pub fn oggpack_writetrunc(b: &mut OggpackBuffer, bits: i64) {
    let bytes = bits >> 3;
    let mut buffer_guard = b.buffer.lock().unwrap();
    let mut ptr_guard = b.ptr.lock().unwrap();
    if !ptr_guard.is_empty() {
        let bits = bits - bytes * 8;
        *ptr_guard = buffer_guard.split_off(bytes as usize);
        b.endbit = bits as i32;
        b.endbyte = bytes;
        if let Some(first_byte) = ptr_guard.first_mut() {
            *first_byte &= MASK[bits as usize] as u8;
        }
    }
}
