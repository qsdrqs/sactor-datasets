#[no_mangle]
pub unsafe fn oggpack_writecopy(
    b: *mut oggpack_buffer,
    source: *mut libc::c_void,
    bits: libc::c_long,
) {
    unsafe extern "C" fn wrapper(b: *mut oggpack_buffer, value: libc::c_ulong, bits: libc::c_int) {
        oggpack_write(b, value, bits);
    }
    oggpack_writecopy_helper(b, source, bits, wrapper, 0);
}
