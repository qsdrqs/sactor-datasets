#[derive(Debug)]
pub struct OggSyncState<'a> {
    pub data: &'a mut [u8],
    pub storage: usize,
    pub fill: usize,
    pub returned: usize,
    pub unsynced: bool,
    pub headerbytes: usize,
    pub bodybytes: usize,
}
