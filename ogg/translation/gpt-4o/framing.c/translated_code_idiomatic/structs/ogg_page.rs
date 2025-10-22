use std::borrow::Cow;
#[derive(Debug, Clone)]
pub struct OggPage<'a> {
    pub header: Cow<'a, [u8]>,
    pub body: &'a [u8],
}
impl<'a> OggPage<'a> {
    pub fn new(header: &'a mut [u8], body: &'a [u8]) -> Self {
        OggPage {
            header: Cow::Borrowed(header),
            body,
        }
    }
}
