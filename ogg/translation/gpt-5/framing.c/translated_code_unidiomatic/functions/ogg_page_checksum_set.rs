#[no_mangle]
pub unsafe fn ogg_page_checksum_set(og: *mut ogg_page) {
    if !og.is_null() {
        let og_ref = &mut *og;
        let header = og_ref.header;
        *header.add(22usize) = 0 as libc::c_uchar;
        *header.add(23usize) = 0 as libc::c_uchar;
        *header.add(24usize) = 0 as libc::c_uchar;
        *header.add(25usize) = 0 as libc::c_uchar;
        let mut crc_reg: libc::c_uint = 0;
        crc_reg = _os_update_crc(crc_reg, header, og_ref.header_len as libc::c_int);
        crc_reg = _os_update_crc(crc_reg, og_ref.body, og_ref.body_len as libc::c_int);
        *header.add(22usize) = (crc_reg & 0xff) as libc::c_uchar;
        *header.add(23usize) = ((crc_reg >> 8) & 0xff) as libc::c_uchar;
        *header.add(24usize) = ((crc_reg >> 16) & 0xff) as libc::c_uchar;
        *header.add(25usize) = ((crc_reg >> 24) & 0xff) as libc::c_uchar;
    }
}
