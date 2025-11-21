pub fn ogg_stream_clear<'a>(os: &mut OggStreamState<'a>) -> i32 {
    os.body_data = &mut [];
    os.lacing_vals = &mut [];
    os.granule_vals = &mut [];
    os.body_storage = 0;
    os.body_fill = 0;
    os.body_returned = 0;
    os.lacing_storage = 0;
    os.lacing_fill = 0;
    os.lacing_packet = 0;
    os.lacing_returned = 0;
    os.header = [0u8; 282];
    os.header_fill = 0;
    os.e_o_s = false;
    os.b_o_s = false;
    os.serialno = 0;
    os.pageno = 0;
    os.packetno = 0;
    os.granulepos = 0;
    0
}
