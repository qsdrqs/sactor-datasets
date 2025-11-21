use libc;
pub unsafe fn oggpack_reset(b: *mut oggpack_buffer) {
    if (*b).ptr.is_null() {
        return;
    }
    (*b).ptr = (*b).buffer;
    *(*b).buffer = 0;
    (*b).endbit = 0;
    (*b).endbyte = 0;
}
