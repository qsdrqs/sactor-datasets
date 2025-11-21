use libc;
pub unsafe fn oggpackB_writeinit(b: *mut oggpack_buffer) {
    oggpack_writeinit(b);
}
