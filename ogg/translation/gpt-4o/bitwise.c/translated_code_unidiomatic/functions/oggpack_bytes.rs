use libc;
pub unsafe fn oggpack_bytes(b: *mut oggpack_buffer) -> libc::c_long {
    let b_ref = &*b;
    b_ref.endbyte + ((b_ref.endbit as libc::c_long) + 7) / 8
}
