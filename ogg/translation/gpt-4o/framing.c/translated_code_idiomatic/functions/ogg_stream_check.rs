pub fn ogg_stream_check(os: Option<&mut OggStreamState>) -> i32 {
    if let Some(stream) = os {
        if stream.body_data.is_empty() {
            return -1;
        }
        0
    } else {
        -1
    }
}
