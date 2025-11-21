pub fn _os_update_crc(mut crc: u32, buffer: &[u8]) -> u32 {
    let mut size = buffer.len();
    let mut index = 0;
    while size >= 8 {
        crc ^= ((buffer[index] as u32) << 24)
            | ((buffer[index + 1] as u32) << 16)
            | ((buffer[index + 2] as u32) << 8)
            | (buffer[index + 3] as u32);
        crc = crc_lookup[7][(crc >> 24) as usize]
            ^ crc_lookup[6][((crc >> 16) & 0xFF) as usize]
            ^ crc_lookup[5][((crc >> 8) & 0xFF) as usize]
            ^ crc_lookup[4][(crc & 0xFF) as usize]
            ^ crc_lookup[3][buffer[index + 4] as usize]
            ^ crc_lookup[2][buffer[index + 5] as usize]
            ^ crc_lookup[1][buffer[index + 6] as usize]
            ^ crc_lookup[0][buffer[index + 7] as usize];
        index += 8;
        size -= 8;
    }
    while size > 0 {
        crc = (crc << 8) ^ crc_lookup[0][(((crc >> 24) & 0xFF) ^ (buffer[index] as u32)) as usize];
        index += 1;
        size -= 1;
    }
    crc
}
