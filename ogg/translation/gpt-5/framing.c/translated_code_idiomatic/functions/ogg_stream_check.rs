pub fn ogg_stream_check(os: Option<&OggStreamState<'_>>) -> i32 {
    if os.is_none() {
        -1
    } else {
        0
    }
}
