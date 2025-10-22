#[derive(Debug)]
pub struct OggSyncState<'a> {
    pub data: &'a mut [u8],
    pub storage: i32,
    pub fill: i32,
    pub returned: i32,
    pub unsynced: i32,
    pub headerbytes: i32,
    pub bodybytes: i32,
}
