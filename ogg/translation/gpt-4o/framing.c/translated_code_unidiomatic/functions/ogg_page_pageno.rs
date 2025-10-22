use libc;
pub unsafe fn ogg_page_pageno(og: *const ogg_page) -> libc::c_long {
    let header = (*og).header;
    let pageno = (*header.offset(18) as libc::c_uint)
        | ((*header.offset(19) as libc::c_uint) << 8)
        | ((*header.offset(20) as libc::c_uint) << 16)
        | ((*header.offset(21) as libc::c_uint) << 24);
    pageno as libc::c_long
}
