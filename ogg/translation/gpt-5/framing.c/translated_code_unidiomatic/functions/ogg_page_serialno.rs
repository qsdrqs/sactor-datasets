#[no_mangle]
pub unsafe fn ogg_page_serialno(og: *const ogg_page) -> libc::c_int {
    let header = (*og).header;
    let v = (*header.add(14)) as u32
        | ((*header.add(15)) as u32) << 8
        | ((*header.add(16)) as u32) << 16
        | ((*header.add(17)) as u32) << 24;
    v as libc::c_int
}
