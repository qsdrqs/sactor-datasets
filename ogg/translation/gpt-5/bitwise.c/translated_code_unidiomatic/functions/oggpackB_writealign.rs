pub unsafe fn oggpackB_writealign(b: *mut oggpack_buffer) {
    let bits: libc::c_int = 8 - (*b).endbit;
    if bits < 8 {
        oggpackB_write(b, 0 as libc::c_ulong, bits);
    }
}
