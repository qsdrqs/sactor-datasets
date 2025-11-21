use libc::{c_void, free, memset};
pub unsafe fn oggpack_writeclear(b: *mut oggpack_buffer) {
    if !(*b).buffer.is_null() {
        free((*b).buffer as *mut c_void);
    }
    memset(b as *mut c_void, 0, std::mem::size_of::<oggpack_buffer>());
}
