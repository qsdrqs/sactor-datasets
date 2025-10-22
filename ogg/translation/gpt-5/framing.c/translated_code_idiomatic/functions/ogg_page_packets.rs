pub fn ogg_page_packets(og: &OggPage<'_>) -> i32 {
    let header: &[u8] = og.header;
    let n = *header.get(26).unwrap_or(&0) as usize;
    header
        .get(27..)
        .unwrap_or(&[])
        .iter()
        .take(n)
        .filter(|&&b| b < 255)
        .count() as i32
}
