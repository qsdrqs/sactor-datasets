#[no_mangle]
pub unsafe fn ogg_page_bos(og: *const ogg_page) -> libc::c_int {
    (*(*og).header.add(5) & 0x02u8) as libc::c_int
}
