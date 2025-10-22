pub fn ogg_packet_clear(op: &mut OggPacket<'_>) {
    op.packet.fill(0);
    op.b_o_s = false;
    op.e_o_s = false;
    op.granulepos = 0;
    op.packetno = 0;
}
