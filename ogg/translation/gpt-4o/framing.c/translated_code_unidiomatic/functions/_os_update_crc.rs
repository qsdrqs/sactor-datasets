pub unsafe fn _os_update_crc(
    mut crc: libc::c_uint,
    mut buffer: *mut libc::c_uchar,
    mut size: libc::c_int,
) -> libc::c_uint {
    while size >= 8 {
        crc ^= ((*buffer.offset(0) as libc::c_uint) << 24)
            | ((*buffer.offset(1) as libc::c_uint) << 16)
            | ((*buffer.offset(2) as libc::c_uint) << 8)
            | (*buffer.offset(3) as libc::c_uint);
        crc = crc_lookup[7][(crc >> 24) as usize]
            ^ crc_lookup[6][((crc >> 16) & 0xFF) as usize]
            ^ crc_lookup[5][((crc >> 8) & 0xFF) as usize]
            ^ crc_lookup[4][(crc & 0xFF) as usize]
            ^ crc_lookup[3][*buffer.offset(4) as usize]
            ^ crc_lookup[2][*buffer.offset(5) as usize]
            ^ crc_lookup[1][*buffer.offset(6) as usize]
            ^ crc_lookup[0][*buffer.offset(7) as usize];
        buffer = buffer.offset(8);
        size -= 8;
    }
    while size > 0 {
        crc =
            (crc << 8) ^ crc_lookup[0][(((crc >> 24) & 0xFF) ^ (*buffer as libc::c_uint)) as usize];
        buffer = buffer.offset(1);
        size -= 1;
    }
    crc
}
