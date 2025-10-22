pub fn ogg_stream_eos(os: Option<&OggStreamState<'_>>) -> i32 {
    if ogg_stream_check(os) != 0 {
        return 1;
    }
    match os {
        Some(s) => {
            if s.e_o_s {
                1
            } else {
                0
            }
        }
        None => 1,
    }
}
