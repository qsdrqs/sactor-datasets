pub fn oggpackB_bytes(b: *mut oggpack_buffer) -> libc::c_long {
    unsafe { oggpack_bytes(b) }
}
