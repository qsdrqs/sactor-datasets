pub fn oggpackB_look1(b: &OggPackBuffer) -> Option<u8> {
    if b.endbyte >= b.storage {
        return None;
    }
    if !(0..=7).contains(&b.endbit) {
        return None;
    }
    let available = b.storage.min(b.buffer.len());
    if b.ptr >= available {
        return None;
    }
    let byte0 = b.buffer[b.ptr] as u32;
    let shift = (7 - b.endbit) as u32;
    let bit = ((byte0 >> shift) & 1) as u8;
    Some(bit)
}
