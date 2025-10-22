#[derive(Debug)]
pub struct OggPackBuffer<'a> {
    pub endbyte: usize,
    pub endbit: i32,
    pub buffer: &'a mut [u8],
    pub ptr: usize,
    pub storage: usize,
}
