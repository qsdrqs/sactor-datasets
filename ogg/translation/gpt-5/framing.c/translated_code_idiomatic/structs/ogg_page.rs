#[derive(Debug)]
pub struct OggPage<'a> {
    pub header: &'a mut [u8],
    pub body: &'a [u8],
}
