#[no_mangle]
pub unsafe fn oggpackB_bits(b: *mut oggpack_buffer) -> libc::c_long {
    oggpack_bits(b)
}
