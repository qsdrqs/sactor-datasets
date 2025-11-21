#[no_mangle]
pub unsafe fn oggpack_bits(b: *mut oggpack_buffer) -> libc::c_long {
    let b_ref = &*b;
    b_ref
        .endbyte
        .wrapping_mul(8 as libc::c_long)
        .wrapping_add(b_ref.endbit as libc::c_long)
}
