pub fn ogg_stream_reset_serialno(os: &mut OggStreamState<'_>, serialno: i32) -> i32 {
    if ogg_stream_check(Some(&*os)) != 0 {
        return -1;
    }
    let _ = ogg_stream_reset(os);
    os.serialno = serialno as u32;
    0
}
