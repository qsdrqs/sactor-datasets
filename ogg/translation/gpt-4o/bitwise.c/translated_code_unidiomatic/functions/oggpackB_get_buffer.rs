pub unsafe fn oggpackB_get_buffer(b: *mut oggpack_buffer) -> *mut libc::c_uchar {
    oggpack_get_buffer(b)
}
