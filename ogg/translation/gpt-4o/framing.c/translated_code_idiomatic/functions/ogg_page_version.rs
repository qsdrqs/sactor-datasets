pub fn ogg_page_version(og: Option<&OggPage>) -> i32 {
    if let Some(og) = og {
        if og.header.len() > 4 {
            return og.header[4] as i32;
        }
    }
    0
}
