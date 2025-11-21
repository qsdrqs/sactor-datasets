pub fn ogg_page_eos(og: Option<&OggPage>) -> i32 {
    if let Some(og_page) = og {
        if og_page.header.len() > 5 {
            return (og_page.header[5] & 0x04) as i32;
        }
    }
    0
}
