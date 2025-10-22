pub fn oggpack_adv1(b: &mut OggpackBuffer) {
    let mut ptr_guard = b.ptr.lock().unwrap();
    if b.endbit < 7 {
        b.endbit += 1;
    } else {
        b.endbit = 0;
        if b.endbyte < b.storage {
            b.endbyte += 1;
            if b.endbyte < ptr_guard.len() as i64 {
                ptr_guard[b.endbyte as usize] = 0;
            }
        }
    }
}
