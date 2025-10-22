use libc;
pub unsafe fn ogg_page_version(og: *const ogg_page) -> i32 {
    if og.is_null() {
        return 0;
    }
    let header = (*og).header;
    if header.is_null() {
        return 0;
    }
    *header.offset(4) as i32
}
