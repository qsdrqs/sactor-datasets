#[no_mangle]
pub unsafe fn oggpackB_writeclear(b: *mut oggpack_buffer) {
    oggpack_writeclear(b);
}
