pub fn ogg_stream_init<'a>(os: &mut OggStreamState<'a>, serialno: i32) -> i32 {
    const MIN_BODY: usize = 16 * 1024;
    const MIN_LACING: usize = 1024;
    if os.body_data.len() < MIN_BODY {
        let buf = vec![0u8; MIN_BODY].into_boxed_slice();
        let leaked: &'static mut [u8] = Box::leak(buf);
        os.body_data = leaked;
    }
    let mut lacing_cap = core::cmp::min(os.lacing_vals.len(), os.granule_vals.len());
    if lacing_cap < MIN_LACING {
        let lacing = vec![0i32; MIN_LACING].into_boxed_slice();
        let granule = vec![0i64; MIN_LACING].into_boxed_slice();
        let lacing_leaked: &'static mut [i32] = Box::leak(lacing);
        let granule_leaked: &'static mut [i64] = Box::leak(granule);
        os.lacing_vals = lacing_leaked;
        os.granule_vals = granule_leaked;
        lacing_cap = MIN_LACING;
    }
    os.body_storage = os.body_data.len();
    os.body_fill = 0;
    os.body_returned = 0;
    os.lacing_storage = lacing_cap;
    os.lacing_fill = 0;
    os.lacing_packet = 0;
    os.lacing_returned = 0;
    os.header = [0u8; 282];
    os.header_fill = 0;
    os.e_o_s = false;
    os.b_o_s = false;
    os.serialno = serialno as u32;
    os.pageno = 0;
    os.packetno = 0;
    os.granulepos = 0;
    0
}
