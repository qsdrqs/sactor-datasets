#[no_mangle]
pub unsafe fn ogg_page_version(og: *const ogg_page) -> libc::c_int {
    (*(*og).header.add(4)) as libc::c_int
}
