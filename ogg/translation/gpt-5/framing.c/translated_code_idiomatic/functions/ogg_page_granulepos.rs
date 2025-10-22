pub fn ogg_page_granulepos(og: &OggPage<'_>) -> i64 {
    if let Some(bytes) = og.header.get(6..14) {
        let mut buf = [0u8; 8];
        buf.copy_from_slice(bytes);
        i64::from_le_bytes(buf)
    } else {
        0
    }
}
