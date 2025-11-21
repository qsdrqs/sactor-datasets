#[no_mangle]
pub fn oggpackB_readinit(b: *mut oggpack_buffer, buf: *mut libc::c_uchar, bytes: libc::c_int) {
    unsafe {
        oggpack_readinit(b, buf, bytes);
    }
}
