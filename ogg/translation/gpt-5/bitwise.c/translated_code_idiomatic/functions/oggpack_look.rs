pub fn oggpack_look(b: &OggPackBuffer, bits: i32) -> i64 {
    if bits < 0 || bits > 32 {
        return -1;
    }
    let endbit_i = b.endbit;
    let mut bits_total = bits + endbit_i;
    if bits_total == 0 {
        return 0;
    }
    let needed_bytes = ((bits_total + 7) >> 3) as usize;
    let avail_len = b.storage.min(b.buffer.len());
    let base = b.ptr;
    if base > avail_len.saturating_sub(needed_bytes) {
        return -1;
    }
    let buf = &b.buffer;
    let ebit = endbit_i as u32;
    let mut ret: u64 = (buf[base] as u64) >> ebit;
    if bits_total > 8 {
        ret |= (buf[base + 1] as u64) << (8 - ebit);
        if bits_total > 16 {
            ret |= (buf[base + 2] as u64) << (16 - ebit);
            if bits_total > 24 {
                ret |= (buf[base + 3] as u64) << (24 - ebit);
                if bits_total > 32 && endbit_i != 0 {
                    ret |= (buf[base + 4] as u64) << (32 - ebit);
                }
            }
        }
    }
    let m = MASK[bits as usize] as u64;
    (ret & m) as i64
}
