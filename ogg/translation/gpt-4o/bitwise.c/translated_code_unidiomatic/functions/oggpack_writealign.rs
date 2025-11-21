pub unsafe fn oggpack_writealign(b: *mut oggpack_buffer) {
    let bits = 8 - (*b).endbit;
    if bits < 8 {
        oggpack_write(b, 0, bits);
    }
}
