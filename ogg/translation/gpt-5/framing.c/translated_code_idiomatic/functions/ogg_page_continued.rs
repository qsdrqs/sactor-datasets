pub fn ogg_page_continued(og: &OggPage<'_>) -> i32 {
    let header: &[u8] = &*og.header;
    let byte = header[5];
    (byte & 1) as i32
}
