pub unsafe fn oggpack_writeinit(b: *mut oggpack_buffer) {
    libc::memset(
        b as *mut libc::c_void,
        0,
        core::mem::size_of::<oggpack_buffer>() as libc::size_t,
    );
    let mem = libc::malloc(256) as *mut libc::c_uchar;
    (*b).buffer = mem;
    (*b).ptr = mem;
    if (*b).buffer.is_null() {
        return;
    }
    *(*b).buffer = 0;
    (*b).storage = 256;
}
