#[derive(Debug)]
pub struct OggPacket<'a> {
    pub packet: &'a mut [u8],
    pub b_o_s: bool,
    pub e_o_s: bool,
    pub granulepos: i64,
    pub packetno: i64,
}
