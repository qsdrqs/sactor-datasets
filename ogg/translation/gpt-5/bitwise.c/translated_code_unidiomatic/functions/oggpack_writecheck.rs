#[no_mangle]
pub unsafe fn oggpack_writecheck(b: *mut oggpack_buffer) -> libc::c_int {
    if (*b).ptr.is_null() || (*b).storage == 0 {
        -1
    } else {
        0
    }
}
