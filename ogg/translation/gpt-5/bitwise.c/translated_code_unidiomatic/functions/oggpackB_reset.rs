#[no_mangle]
pub unsafe fn oggpackB_reset(b: *mut oggpack_buffer) {
    oggpack_reset(b);
}
