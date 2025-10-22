pub fn oggpackB_writetrunc(b: &mut OggpackBuffer, bits: i64) {
    let bytes = bits >> 3;
    let mut buffer_lock = b.buffer.lock().unwrap();
    let mut ptr_lock = b.ptr.lock().unwrap();
    if !ptr_lock.is_empty() {
        let bits = bits - bytes * 8;
        *ptr_lock = buffer_lock.split_off(bytes as usize);
        b.endbit = bits as i32;
        b.endbyte = bytes;
        if let Some(first_byte) = ptr_lock.first_mut() {
            *first_byte &= MASK8B[bits as usize] as u8;
        }
    }
}
