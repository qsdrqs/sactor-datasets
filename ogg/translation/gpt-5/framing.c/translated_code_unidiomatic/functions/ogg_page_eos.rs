pub unsafe fn ogg_page_eos(og: *const ogg_page) -> libc::c_int {
    let header = (*og).header;
    ((*header.add(5)) as libc::c_int) & 0x04
}
