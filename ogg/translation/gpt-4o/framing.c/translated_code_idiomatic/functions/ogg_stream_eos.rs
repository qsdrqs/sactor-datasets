pub fn ogg_stream_eos(os: Option<&mut OggStreamState>) -> i32 {
    if let Some(stream) = os {
        if ogg_stream_check(Some(stream)) != 0 {
            return 1;
        }
        stream.e_o_s
    } else {
        1
    }
}
