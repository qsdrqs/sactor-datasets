pub fn oggpack_look(b: &OggpackBuffer, bits: i32) -> i64 {
    if bits < 0 || bits > 32 {
        return -1;
    }
    let m = MASK[bits as usize] as u64;
    let bits = bits + b.endbit;
    let storage = b.storage as usize;
    let endbyte = b.endbyte as usize;
    let ptr = b.ptr.lock().unwrap();
    if endbyte >= storage - 4 {
        if endbyte > storage - ((bits + 7) as usize >> 3) {
            return -1;
        } else if bits == 0 {
            return 0;
        }
    }
    let mut ret = (ptr[0] as u64) >> b.endbit;
    if bits > 8 {
        ret |= (ptr[1] as u64) << (8 - b.endbit);
        if bits > 16 {
            ret |= (ptr[2] as u64) << (16 - b.endbit);
            if bits > 24 {
                ret |= (ptr[3] as u64) << (24 - b.endbit);
                if bits > 32 && b.endbit != 0 {
                    ret |= (ptr[4] as u64) << (32 - b.endbit);
                }
            }
        }
    }
    (m & ret) as i64
}
