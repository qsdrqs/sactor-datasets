pub fn ogg_stream_packetin<'a>(os: &mut OggStreamState<'a>, op: &OggPacket<'a>) -> i32 {
    let packet_bytes: &[u8] = &op.packet[..];
    let iov = [OggIovec {
        iov_base: packet_bytes,
    }];
    ogg_stream_iovecin(os, Some(&iov), op.e_o_s, op.granulepos)
}
