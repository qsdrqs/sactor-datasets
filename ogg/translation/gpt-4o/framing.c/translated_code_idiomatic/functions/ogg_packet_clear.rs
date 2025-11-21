pub fn ogg_packet_clear(op: &mut OggPacket) {
    op.packet = &[];
    op.bytes = 0;
    op.b_o_s = 0;
    op.e_o_s = 0;
    op.granulepos = 0;
    op.packetno = 0;
}
