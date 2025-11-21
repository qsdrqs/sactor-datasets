#[no_mangle]
pub unsafe fn oggpackB_look1(b: *mut oggpack_buffer) -> libc::c_long {
    if (*b).endbyte >= (*b).storage {
        return -1;
    }
    let byte0 = *(*b).ptr as libc::c_uint;
    let shift = (7 - (*b).endbit) as u32;
    ((byte0.wrapping_shr(shift) & 1u32) as libc::c_long)
}
