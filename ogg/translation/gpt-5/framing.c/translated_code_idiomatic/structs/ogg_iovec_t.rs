#[derive(Copy, Clone, Debug)]
pub struct OggIovec<'a> {
    pub iov_base: &'a [u8],
}
