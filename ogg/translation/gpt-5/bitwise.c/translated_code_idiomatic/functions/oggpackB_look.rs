pub fn oggpackB_look(b: &OggPackBuffer<'_>, bits: i32) -> i64 {
    let m = 32 - bits;
    if m < 0 || m > 32 {
        return -1;
    }
    if bits == 0 {
        return 0;
    }
    let bits_total = bits + b.endbit;
    if b.endbyte >= b.storage.saturating_sub(4) {
        let needed_bytes = ((bits_total + 7) >> 3) as usize;
        if b.endbyte > b.storage.saturating_sub(needed_bytes) {
            return -1;
        } else if bits_total == 0 {
            return 0;
        }
    }
    let base = b.ptr;
    let bytes_to_read = if bits_total <= 8 {
        1
    } else if bits_total <= 16 {
        2
    } else if bits_total <= 24 {
        3
    } else if bits_total <= 32 {
        4
    } else if b.endbit != 0 {
        5
    } else {
        4
    };
    let max_len = b.buffer.len().min(b.storage);
    if base + bytes_to_read > max_len {
        return -1;
    }
    let endbit_u = b.endbit as u32;
    let mut ret: u64 = (b.buffer[base] as u64) << (24 + endbit_u);
    if bits_total > 8 {
        ret |= (b.buffer[base + 1] as u64) << (16 + endbit_u);
        if bits_total > 16 {
            ret |= (b.buffer[base + 2] as u64) << (8 + endbit_u);
            if bits_total > 24 {
                ret |= (b.buffer[base + 3] as u64) << endbit_u;
                if bits_total > 32 && b.endbit != 0 {
                    ret |= (b.buffer[base + 4] as u64) >> (8 - endbit_u);
                }
            }
        }
    }
    let ret32 = ret & 0xffff_ffffu64;
    let sh1: u32 = (m >> 1) as u32;
    let sh2: u32 = ((m + 1) >> 1) as u32;
    ((ret32 >> sh1) >> sh2) as i64
}
