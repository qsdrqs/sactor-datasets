pub unsafe fn ogg_page_granulepos(og: *const ogg_page) -> libc::c_long {
    let page = (*og).header;
    let mut granulepos: libc::c_ulong = (*page.add(13)) as libc::c_ulong & 0xff;
    granulepos = (granulepos << 8) | ((*page.add(12)) as libc::c_ulong & 0xff);
    granulepos = (granulepos << 8) | ((*page.add(11)) as libc::c_ulong & 0xff);
    granulepos = (granulepos << 8) | ((*page.add(10)) as libc::c_ulong & 0xff);
    granulepos = (granulepos << 8) | ((*page.add(9)) as libc::c_ulong & 0xff);
    granulepos = (granulepos << 8) | ((*page.add(8)) as libc::c_ulong & 0xff);
    granulepos = (granulepos << 8) | ((*page.add(7)) as libc::c_ulong & 0xff);
    granulepos = (granulepos << 8) | ((*page.add(6)) as libc::c_ulong & 0xff);
    granulepos as libc::c_long
}
