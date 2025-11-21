pub fn ogg_page_packets(og: &OggPage) -> i32 {
    let n = og.header[26] as i32;
    let mut count = 0;
    for &byte in &og.header[27..27 + n as usize] {
        if byte < 255 {
            count += 1;
        }
    }
    count
}
