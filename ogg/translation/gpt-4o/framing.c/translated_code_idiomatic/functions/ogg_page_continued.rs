pub fn ogg_page_continued(og: Option<&OggPage>) -> i32 {
    if let Some(page) = og {
        if let Some(&byte) = page.header.get(5) {
            return (byte & 0x01) as i32;
        }
    }
    0
}
