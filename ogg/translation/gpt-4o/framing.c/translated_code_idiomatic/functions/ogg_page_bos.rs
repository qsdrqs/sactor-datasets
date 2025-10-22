pub fn ogg_page_bos(og: &OggPage) -> i32 {
    if og.header.len() < 6 {
        return 0;
    }
    (og.header[5] & 0x02) as i32
}
