pub fn ogg_stream_destroy(os: Option<&mut OggStreamState>) -> i32 {
    if let Some(os) = os {
        ogg_stream_clear(Some(os));
    }
    0
}
