pub fn ogg_stream_init(os: Option<&mut OggStreamState>, serialno: i32) -> i32 {
    if let Some(os) = os {
        fn initialize_state(serialno: i32) -> OggStreamState<'static> {
            let body_storage = 16 * 1024;
            let lacing_storage = 1024;
            let mut body_data = vec![0u8; body_storage as usize];
            let mut lacing_vals = vec![0i32; lacing_storage as usize];
            let mut granule_vals = vec![0i64; lacing_storage as usize];
            OggStreamState {
                body_data: Box::leak(body_data.into_boxed_slice()),
                body_storage: body_storage as i64,
                body_fill: 0,
                body_returned: 0,
                lacing_vals: Box::leak(lacing_vals.into_boxed_slice()),
                granule_vals: Box::leak(granule_vals.into_boxed_slice()),
                lacing_storage: lacing_storage as i64,
                lacing_fill: 0,
                lacing_packet: 0,
                lacing_returned: 0,
                header: [0; 282],
                header_fill: 0,
                e_o_s: 0,
                b_o_s: 0,
                serialno: serialno as i64,
                pageno: 0,
                packetno: 0,
                granulepos: 0,
            }
        }
        let new_state = initialize_state(serialno);
        *os = new_state;
        0
    } else {
        -1
    }
}
