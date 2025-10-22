pub unsafe fn ogg_page_serialno(og: *const ogg_page) -> i32 {
    let header = (*og).header;
    ((*header.offset(14) as u32)
        | ((*header.offset(15) as u32) << 8)
        | ((*header.offset(16) as u32) << 16)
        | ((*header.offset(17) as u32) << 24)) as i32
}
