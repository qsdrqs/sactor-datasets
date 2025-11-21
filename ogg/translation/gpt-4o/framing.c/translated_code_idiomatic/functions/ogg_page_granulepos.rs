pub fn ogg_page_granulepos(og: &OggPage) -> i64 {
    let page = &og.header;
    let mut granulepos: u64 = (page[13] & 0xff) as u64;
    granulepos = (granulepos << 8) | ((page[12] & 0xff) as u64);
    granulepos = (granulepos << 8) | ((page[11] & 0xff) as u64);
    granulepos = (granulepos << 8) | ((page[10] & 0xff) as u64);
    granulepos = (granulepos << 8) | ((page[9] & 0xff) as u64);
    granulepos = (granulepos << 8) | ((page[8] & 0xff) as u64);
    granulepos = (granulepos << 8) | ((page[7] & 0xff) as u64);
    granulepos = (granulepos << 8) | ((page[6] & 0xff) as u64);
    granulepos as i64
}
