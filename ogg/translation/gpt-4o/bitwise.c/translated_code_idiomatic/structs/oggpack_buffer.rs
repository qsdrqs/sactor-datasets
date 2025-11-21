use std::sync::{Arc, Mutex};
#[derive(Debug)]
pub struct OggpackBuffer {
    pub endbyte: i64,
    pub endbit: i32,
    pub buffer: Arc<Mutex<Vec<u8>>>,
    pub ptr: Arc<Mutex<Vec<u8>>>,
    pub storage: i64,
}
impl Clone for OggpackBuffer {
    fn clone(&self) -> Self {
        OggpackBuffer {
            endbyte: self.endbyte,
            endbit: self.endbit,
            buffer: Arc::clone(&self.buffer),
            ptr: Arc::clone(&self.ptr),
            storage: self.storage,
        }
    }
}
