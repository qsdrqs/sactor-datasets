#[no_mangle]
pub fn oggpackB_writecheck(b: *mut oggpack_buffer) -> libc::c_int {
    unsafe { oggpack_writecheck(b) }
}
