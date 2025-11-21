pub fn ogg_stream_reset_serialno(os: &mut OggStreamState, serialno: i32) -> i32 {
    if ogg_stream_check(Some(os)) != 0 {
        return -1;
    }
    ogg_stream_reset(os);
    os.serialno = serialno as i64;
    0
}
