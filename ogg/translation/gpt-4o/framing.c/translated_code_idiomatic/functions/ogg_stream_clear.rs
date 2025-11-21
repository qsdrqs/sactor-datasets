pub fn ogg_stream_clear(os: Option<&mut OggStreamState>) -> i32 {
    if let Some(stream) = os {
        stream.body_data.fill(0);
        stream.lacing_vals.fill(0);
        stream.granule_vals.fill(0);
        *stream = OggStreamState {
            body_data: &mut [],
            body_storage: 0,
            body_fill: 0,
            body_returned: 0,
            lacing_vals: &mut [],
            granule_vals: &mut [],
            lacing_storage: 0,
            lacing_fill: 0,
            lacing_packet: 0,
            lacing_returned: 0,
            header: [0; 282],
            header_fill: 0,
            e_o_s: 0,
            b_o_s: 0,
            serialno: 0,
            pageno: 0,
            packetno: 0,
            granulepos: 0,
        };
    }
    0
}
