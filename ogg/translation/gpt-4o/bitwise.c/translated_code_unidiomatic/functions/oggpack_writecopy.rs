use libc::{c_long, c_void};
pub unsafe fn oggpack_writecopy(b: *mut oggpack_buffer, source: *mut c_void, bits: c_long) {
    unsafe extern "C" fn oggpack_write_wrapper(
        b: *mut oggpack_buffer,
        value: libc::c_ulong,
        bits: libc::c_int,
    ) {
        unsafe {
            oggpack_write(b, value as u32, bits);
        }
    }
    oggpack_writecopy_helper(b, source, bits, oggpack_write_wrapper, 0);
}
