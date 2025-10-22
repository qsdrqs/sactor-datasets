pub unsafe fn ogg_page_continued(og: *const ogg_page) -> i32 {
    if og.is_null() {
        return 0;
    }
    let header = (*og).header;
    if header.is_null() {
        return 0;
    }
    (*header.offset(5) & 0x01) as i32
}
