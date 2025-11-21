pub unsafe fn oggpack_readinit(
    b: *mut oggpack_buffer,
    buf: *mut libc::c_uchar,
    bytes: libc::c_int,
) {
    libc::memset(
        b as *mut libc::c_void,
        0,
        core::mem::size_of::<oggpack_buffer>() as libc::size_t,
    );
    (*b).ptr = buf;
    (*b).buffer = buf;
    (*b).storage = bytes as libc::c_long;
}
