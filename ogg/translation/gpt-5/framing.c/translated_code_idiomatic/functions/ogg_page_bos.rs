#[no_mangle]
pub fn ogg_page_bos(og: &OggPage<'_>) -> i32 {
    let b = og.header.get(5).copied().unwrap_or(0);
    (b & 0x02) as i32
}
