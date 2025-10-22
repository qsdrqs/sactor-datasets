pub fn ogg_page_version(og: &OggPage<'_>) -> i32 {
    og.header[4] as i32
}
