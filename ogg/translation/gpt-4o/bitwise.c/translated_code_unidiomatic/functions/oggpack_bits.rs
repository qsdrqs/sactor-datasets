use libc;
pub unsafe fn oggpack_bits(b: *mut oggpack_buffer) -> libc::c_long {
    let b_ref = &*b;
    b_ref.endbyte * 8 + b_ref.endbit as libc::c_long
}
