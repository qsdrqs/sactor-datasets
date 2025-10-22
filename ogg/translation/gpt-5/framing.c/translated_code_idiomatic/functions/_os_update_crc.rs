pub fn _os_update_crc(mut crc: u32, buffer: &[u8]) -> u32 {
    let mut chunks = buffer.chunks_exact(8);
    for chunk in &mut chunks {
        let b0 = chunk[0] as u32;
        let b1 = chunk[1] as u32;
        let b2 = chunk[2] as u32;
        let b3 = chunk[3] as u32;
        let b4 = chunk[4] as usize;
        let b5 = chunk[5] as usize;
        let b6 = chunk[6] as usize;
        let b7 = chunk[7] as usize;
        let x = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
        let t = crc ^ x;
        crc = crc_lookup[7][(t >> 24) as usize]
            ^ crc_lookup[6][((t >> 16) & 0xFF) as usize]
            ^ crc_lookup[5][((t >> 8) & 0xFF) as usize]
            ^ crc_lookup[4][(t & 0xFF) as usize]
            ^ crc_lookup[3][b4]
            ^ crc_lookup[2][b5]
            ^ crc_lookup[1][b6]
            ^ crc_lookup[0][b7];
    }
    for &byte in chunks.remainder() {
        let idx = (((crc >> 24) & 0xFF) ^ (byte as u32)) as usize;
        crc = (crc << 8) ^ crc_lookup[0][idx];
    }
    crc
}
