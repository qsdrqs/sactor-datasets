pub unsafe fn oggpackB_writecopy(
    b: *mut oggpack_buffer,
    source: *mut libc::c_void,
    bits: libc::c_long,
) {
    unsafe extern "C" fn adapter(b: *mut oggpack_buffer, value: libc::c_ulong, bits: libc::c_int) {
        oggpackB_write(b, value, bits);
    }
    oggpack_writecopy_helper(b, source, bits, adapter, 1 as libc::c_int);
}
