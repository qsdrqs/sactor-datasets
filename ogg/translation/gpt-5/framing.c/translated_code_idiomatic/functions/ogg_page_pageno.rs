pub fn ogg_page_pageno(og: &OggPage<'_>) -> u32 {
    let header: &[u8] = &og.header[..];
    assert!(header.len() >= 22, "Ogg page header too short");
    u32::from_le_bytes([header[18], header[19], header[20], header[21]])
}
