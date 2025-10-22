#[no_mangle]
pub unsafe fn oggpack_writeclear(b: *mut oggpack_buffer) {
    if !(*b).buffer.is_null() {
        libc::free((*b).buffer as *mut libc::c_void);
    }
    libc::memset(
        b as *mut libc::c_void,
        0,
        core::mem::size_of::<oggpack_buffer>(),
    );
}
