#[derive(Debug)]
pub struct OggPacket<'a> {
    pub packet: &'a [u8],
    pub bytes: i64,
    pub b_o_s: i64,
    pub e_o_s: i64,
    pub granulepos: i64,
    pub packetno: i64,
}
impl<'a> OggPacket<'a> {
    pub fn clone(&self) -> OggPacket<'a> {
        OggPacket {
            packet: self.packet,
            bytes: self.bytes,
            b_o_s: self.b_o_s,
            e_o_s: self.e_o_s,
            granulepos: self.granulepos,
            packetno: self.packetno,
        }
    }
}
