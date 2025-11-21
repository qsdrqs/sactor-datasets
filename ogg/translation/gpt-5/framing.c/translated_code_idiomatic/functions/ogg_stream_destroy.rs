pub fn ogg_stream_destroy<'a>(os: Option<Box<OggStreamState<'a>>>) -> i32 {
    if let Some(mut state) = os {
        let _ = ogg_stream_clear(&mut state);
    }
    0
}
