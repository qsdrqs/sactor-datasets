pub unsafe fn oggpack_get_buffer(b: *mut oggpack_buffer) -> *mut libc::c_uchar {
    (*b).buffer
}
