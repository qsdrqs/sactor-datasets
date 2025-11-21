pub fn ogg_page_serialno(og: &OggPage<'_>) -> i32 {
    let header: &[u8] = &*og.header;
    debug_assert!(
        header.len() >= 18,
        "OggPage header must be at least 18 bytes long"
    );
    i32::from_le_bytes([header[14], header[15], header[16], header[17]])
}
