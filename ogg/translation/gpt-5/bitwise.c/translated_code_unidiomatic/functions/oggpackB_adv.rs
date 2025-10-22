#[no_mangle]
pub unsafe fn oggpackB_adv(b: *mut oggpack_buffer, bits: libc::c_int) {
    oggpack_adv(b, bits);
}
