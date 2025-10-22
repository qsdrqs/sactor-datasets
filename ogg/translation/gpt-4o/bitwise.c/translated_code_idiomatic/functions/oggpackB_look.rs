pub fn oggpackB_look(b: &OggpackBuffer, bits: i32) -> i64 {
    let m = 32 - bits;
    if m < 0 || m > 32 {
        return -1;
    }
    let bits = bits + b.endbit;
    let storage = b.storage;
    let endbyte = b.endbyte;
    let ptr_guard = b.ptr.lock().unwrap();
    let ptr = &*ptr_guard;
    if endbyte >= storage - 4 {
        if endbyte > storage - ((bits as i64 + 7) >> 3) {
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    let mut ret: u64 = (ptr[0] as u64) << (24 + b.endbit);
    if bits > 8 {
        ret |= (ptr[1] as u64) << (16 + b.endbit);
        if bits > 16 {
            ret |= (ptr[2] as u64) << (8 + b.endbit);
            if bits > 24 {
                ret |= (ptr[3] as u64) << b.endbit;
                if bits > 32 && b.endbit != 0 {
                    ret |= (ptr[4] as u64) >> (8 - b.endbit);
                }
            }
        }
    }
    (((ret & 0xffffffff) >> (m >> 1)) >> ((m + 1) >> 1)) as i64
}
