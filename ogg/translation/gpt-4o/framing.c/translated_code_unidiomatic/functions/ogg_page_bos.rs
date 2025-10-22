use libc;
pub unsafe fn ogg_page_bos(og: *const ogg_page) -> libc::c_int {
    if og.is_null() {
        return 0;
    }
    let header = (*og).header;
    if header.is_null() {
        return 0;
    }
    (*header.offset(5) & 0x02) as libc::c_int
}
