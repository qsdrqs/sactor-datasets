#[no_mangle]
pub unsafe fn oggpackB_bytes(b: *mut oggpack_buffer) -> libc::c_long {
    oggpack_bytes(b)
}
