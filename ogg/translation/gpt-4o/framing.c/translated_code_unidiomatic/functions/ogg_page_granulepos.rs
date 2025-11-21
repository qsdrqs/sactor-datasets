pub unsafe fn ogg_page_granulepos(og: *const ogg_page) -> libc::c_long {
    let page = (*og).header;
    let mut granulepos: u64 = (*page.add(13) & 0xff) as u64;
    granulepos = (granulepos << 8) | ((*page.add(12) & 0xff) as u64);
    granulepos = (granulepos << 8) | ((*page.add(11) & 0xff) as u64);
    granulepos = (granulepos << 8) | ((*page.add(10) & 0xff) as u64);
    granulepos = (granulepos << 8) | ((*page.add(9) & 0xff) as u64);
    granulepos = (granulepos << 8) | ((*page.add(8) & 0xff) as u64);
    granulepos = (granulepos << 8) | ((*page.add(7) & 0xff) as u64);
    granulepos = (granulepos << 8) | ((*page.add(6) & 0xff) as u64);
    granulepos as libc::c_long
}
