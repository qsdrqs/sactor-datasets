#[no_mangle]
pub unsafe fn ogg_page_continued(og: *const ogg_page) -> libc::c_int {
    let header = (*og).header as *const libc::c_uchar;
    let byte = *header.add(5);
    (byte & (1 as libc::c_uchar)) as libc::c_int
}
