use libc;
pub unsafe fn oggpackB_readinit(
    b: *mut oggpack_buffer,
    buf: *mut libc::c_uchar,
    bytes: libc::c_int,
) {
    oggpack_readinit(b, buf, bytes);
}
