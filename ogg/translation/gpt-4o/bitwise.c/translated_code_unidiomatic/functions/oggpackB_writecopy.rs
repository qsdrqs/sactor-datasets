use libc::{c_long, c_void};
pub unsafe fn oggpackB_writecopy(b: *mut oggpack_buffer, source: *mut c_void, bits: c_long) {
    extern "C" {
        fn oggpackB_write(b: *mut oggpack_buffer, value: libc::c_ulong, bits: libc::c_int);
    }
    oggpack_writecopy_helper(b, source, bits, oggpackB_write, 1);
}
