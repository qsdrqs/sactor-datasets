pub fn oggpackB_read(b: &mut OggPackBuffer<'_>, mut bits: i32) -> i64 {
    fn set_error(b: &mut OggPackBuffer<'_>) {
        b.ptr = b.storage;
        b.endbyte = b.storage;
        b.endbit = 1;
    }
    let m_i32 = 32 - bits;
    if m_i32 < 0 || m_i32 > 32 {
        set_error(b);
        return -1;
    }
    bits += b.endbit;
    let bits_total = bits;
    let remaining = b.storage.saturating_sub(b.endbyte);
    if remaining <= 4 {
        let need_bytes = ((bits_total + 7) >> 3) as usize;
        if b.endbyte > b.storage.saturating_sub(need_bytes) {
            set_error(b);
            return -1;
        } else if bits_total == 0 {
            return 0;
        }
    }
    let p = b.ptr;
    let endbit_u32 = b.endbit as u32;
    let mut ret_u: u64 = (b.buffer[p] as u64) << (24u32 + endbit_u32);
    if bits_total > 8 {
        ret_u |= (b.buffer[p + 1] as u64) << (16u32 + endbit_u32);
        if bits_total > 16 {
            ret_u |= (b.buffer[p + 2] as u64) << (8u32 + endbit_u32);
            if bits_total > 24 {
                ret_u |= (b.buffer[p + 3] as u64) << endbit_u32;
                if bits_total > 32 && b.endbit != 0 {
                    ret_u |= (b.buffer[p + 4] as u64) >> (8u32 - endbit_u32);
                }
            }
        }
    }
    let m_u32 = m_i32 as u32;
    ret_u = ((ret_u & 0xffff_ffffu64) >> (m_u32 >> 1)) >> ((m_u32 + 1) >> 1);
    let advance_bytes = (bits_total >> 3) as usize;
    b.ptr = b.ptr.saturating_add(advance_bytes);
    b.endbyte = b.endbyte.saturating_add(advance_bytes);
    b.endbit = (bits_total & 7) as i32;
    ret_u as i64
}
