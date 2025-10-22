use libc;
pub unsafe fn oggpack_readinit(
    b: *mut oggpack_buffer,
    buf: *mut libc::c_uchar,
    bytes: libc::c_int,
) {
    unsafe fn memset(ptr: *mut libc::c_void, value: libc::c_int, num: libc::size_t) {
        libc::memset(ptr, value, num);
    }
    memset(
        b as *mut libc::c_void,
        0,
        std::mem::size_of::<oggpack_buffer>(),
    );
    (*b).buffer = buf;
    (*b).ptr = buf;
    (*b).storage = bytes as libc::c_long;
}
