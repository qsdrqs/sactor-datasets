pub unsafe fn _os_update_crc(
    mut crc: libc::c_uint,
    mut buffer: *mut libc::c_uchar,
    mut size: libc::c_int,
) -> libc::c_uint {
    while size >= 8 {
        let b0 = *buffer.add(0) as libc::c_uint;
        let b1 = *buffer.add(1) as libc::c_uint;
        let b2 = *buffer.add(2) as libc::c_uint;
        let b3 = *buffer.add(3) as libc::c_uint;
        crc ^= (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
        crc = crc_lookup[7][(crc >> 24) as usize]
            ^ crc_lookup[6][((crc >> 16) & 0xFF) as usize]
            ^ crc_lookup[5][((crc >> 8) & 0xFF) as usize]
            ^ crc_lookup[4][(crc & 0xFF) as usize]
            ^ crc_lookup[3][*buffer.add(4) as usize]
            ^ crc_lookup[2][*buffer.add(5) as usize]
            ^ crc_lookup[1][*buffer.add(6) as usize]
            ^ crc_lookup[0][*buffer.add(7) as usize];
        buffer = buffer.add(8);
        size -= 8;
    }
    while {
        let prev = size;
        size -= 1;
        prev != 0
    } {
        let byte = *buffer as libc::c_uint;
        crc = (crc << 8) ^ crc_lookup[0][(((crc >> 24) & 0xFF) ^ byte) as usize];
        buffer = buffer.add(1);
    }
    crc
}
