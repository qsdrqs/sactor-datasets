pub fn oggpack_adv(b: &mut OggPackBuffer<'_>, bits: i32) {
    fn invalidate(b: &mut OggPackBuffer<'_>) {
        b.ptr = b.storage;
        b.endbyte = b.storage;
        b.endbit = 1;
    }
    if bits < 0 {
        invalidate(b);
        return;
    }
    let bits_total = match b.endbit.checked_add(bits) {
        Some(v) => v,
        None => {
            invalidate(b);
            return;
        }
    };
    let needed_bytes = ((bits_total + 7) / 8) as usize;
    if needed_bytes > b.storage.saturating_sub(b.endbyte) {
        invalidate(b);
        return;
    }
    let byte_incr = (bits_total / 8) as usize;
    b.ptr += byte_incr;
    b.endbyte += byte_incr;
    b.endbit = bits_total & 7;
}
