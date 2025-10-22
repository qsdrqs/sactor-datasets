pub fn ogg_page_pageno(og: &OggPage) -> i32 {
    let header = &og.header;
    let pageno = (header[18] as u32)
        | ((header[19] as u32) << 8)
        | ((header[20] as u32) << 16)
        | ((header[21] as u32) << 24);
    pageno as i32
}
