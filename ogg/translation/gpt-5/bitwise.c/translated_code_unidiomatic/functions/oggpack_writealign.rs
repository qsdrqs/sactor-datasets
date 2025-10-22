#[no_mangle]
pub unsafe fn oggpack_writealign(b: *mut oggpack_buffer) {
    let bits: libc::c_int = 8 - (*b).endbit;
    if bits < 8 {
        oggpack_write(b, 0 as libc::c_ulong, bits);
    }
}
