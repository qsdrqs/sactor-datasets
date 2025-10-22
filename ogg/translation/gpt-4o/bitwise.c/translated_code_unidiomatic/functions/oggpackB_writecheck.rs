use libc;
pub unsafe fn oggpackB_writecheck(b: *mut oggpack_buffer) -> libc::c_int {
    oggpack_writecheck(b)
}
