pub unsafe fn ogg_page_pageno(og: *const ogg_page) -> libc::c_long {
    let header = (*og).header as *const libc::c_uchar;
    let v: u32 = (*header.add(18) as u32)
        | ((*header.add(19) as u32) << 8)
        | ((*header.add(20) as u32) << 16)
        | ((*header.add(21) as u32) << 24);
    v as libc::c_long
}
