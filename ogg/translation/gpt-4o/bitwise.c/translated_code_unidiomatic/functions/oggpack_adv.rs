use libc;
pub unsafe fn oggpack_adv(b: *mut oggpack_buffer, bits: libc::c_int) {
    let mut bits = bits + (*b).endbit;
    if (*b).endbyte > (*b).storage - (((bits + 7) >> 3) as libc::c_long) {
        (*b).ptr = std::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
        return;
    }
    (*b).ptr = (*b).ptr.add((bits / 8) as usize);
    (*b).endbyte += (bits / 8) as libc::c_long;
    (*b).endbit = bits & 7;
}
