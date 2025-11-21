use libc::{c_int, c_long, c_uchar, malloc, memset};
pub unsafe fn oggpack_writeinit(b: *mut oggpack_buffer) {
    if b.is_null() {
        return;
    }
    memset(
        b as *mut libc::c_void,
        0,
        std::mem::size_of::<oggpack_buffer>(),
    );
    let buffer = malloc(256) as *mut c_uchar;
    if buffer.is_null() {
        return;
    }
    (*b).buffer = buffer;
    (*b).ptr = buffer;
    *(*b).buffer = b'\0' as c_uchar;
    (*b).storage = 256;
}
