pub fn ogg_page_eos(og: &OggPage<'_>) -> i32 {
    let byte5 = og.header.get(5).copied().unwrap_or(0);
    (byte5 as i32) & 0x04
}
