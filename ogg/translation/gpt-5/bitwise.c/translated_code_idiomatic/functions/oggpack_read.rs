pub fn oggpack_read(b: &mut OggPackBuffer<'_>, mut bits: i32) -> i64 {
    fn fail(b: &mut OggPackBuffer<'_>) -> i64 {
        b.ptr = b.storage;
        b.endbyte = b.storage;
        b.endbit = 1;
        -1
    }
    if bits < 0 || bits > 32 {
        return fail(b);
    }
    let m: u32 = MASK[bits as usize];
    bits += b.endbit;
    if b.endbyte >= b.storage.saturating_sub(4) {
        let need_bytes = ((bits + 7) >> 3) as usize;
        if b.endbyte > b.storage.saturating_sub(need_bytes) {
            return fail(b);
        } else if bits == 0 {
            return 0;
        }
    }
    let p = b.ptr;
    let buf = &b.buffer;
    let mut ret_u: u32 = (buf[p] as u32) >> (b.endbit as u32);
    if bits > 8 {
        let sh1 = (8 - b.endbit) as u32;
        ret_u |= (buf[p + 1] as u32) << sh1;
        if bits > 16 {
            let sh2 = (16 - b.endbit) as u32;
            ret_u |= (buf[p + 2] as u32) << sh2;
            if bits > 24 {
                let sh3 = (24 - b.endbit) as u32;
                ret_u |= (buf[p + 3] as u32) << sh3;
                if bits > 32 && b.endbit != 0 {
                    let sh4 = (32 - b.endbit) as u32;
                    ret_u |= (buf[p + 4] as u32) << sh4;
                }
            }
        }
    }
    ret_u &= m;
    let byte_advance = (bits / 8) as usize;
    b.ptr += byte_advance;
    b.endbyte += byte_advance;
    b.endbit = (bits & 7) as i32;
    ret_u as i64
}
