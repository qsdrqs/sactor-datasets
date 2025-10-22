pub unsafe fn ogg_page_checksum_set(og: *mut ogg_page) {
    if !og.is_null() {
        let mut crc_reg: libc::c_uint = 0;
        let og = &mut *og;
        (*og.header.offset(22)) = 0;
        (*og.header.offset(23)) = 0;
        (*og.header.offset(24)) = 0;
        (*og.header.offset(25)) = 0;
        crc_reg = _os_update_crc(crc_reg, og.header, og.header_len as libc::c_int);
        crc_reg = _os_update_crc(crc_reg, og.body, og.body_len as libc::c_int);
        (*og.header.offset(22)) = (crc_reg & 0xff) as libc::c_uchar;
        (*og.header.offset(23)) = ((crc_reg >> 8) & 0xff) as libc::c_uchar;
        (*og.header.offset(24)) = ((crc_reg >> 16) & 0xff) as libc::c_uchar;
        (*og.header.offset(25)) = ((crc_reg >> 24) & 0xff) as libc::c_uchar;
    }
}
