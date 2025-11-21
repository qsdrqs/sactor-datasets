pub fn ogg_stream_reset(os: &mut OggStreamState<'_>) -> i32 {
    if ogg_stream_check(Some(&*os)) != 0 {
        return -1;
    }
    os.body_fill = 0;
    os.body_returned = 0;
    os.lacing_fill = 0;
    os.lacing_packet = 0;
    os.lacing_returned = 0;
    os.header_fill = 0;
    os.e_o_s = false;
    os.b_o_s = false;
    os.pageno = 0;
    os.packetno = 0;
    os.granulepos = 0;
    0
}
