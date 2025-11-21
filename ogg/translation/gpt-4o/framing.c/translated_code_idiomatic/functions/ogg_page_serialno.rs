pub fn ogg_page_serialno(og: &OggPage) -> i32 {
    let header = &og.header;
    (header[14] as u32
        | (header[15] as u32) << 8
        | (header[16] as u32) << 16
        | (header[17] as u32) << 24) as i32
}
