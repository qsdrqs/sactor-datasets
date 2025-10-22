#[no_mangle]
pub fn oggpackB_writeinit(b: *mut oggpack_buffer) {
    unsafe {
        oggpack_writeinit(b);
    }
}
