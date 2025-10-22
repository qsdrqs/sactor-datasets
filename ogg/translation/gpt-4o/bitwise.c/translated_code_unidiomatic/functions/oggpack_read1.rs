pub unsafe fn oggpack_read1(b: *mut oggpack_buffer) -> libc::c_long {
    let mut ret: libc::c_long;
    if (*b).endbyte >= (*b).storage {
        goto_overflow(b);
        return -1;
    }
    ret = ((*(*b).ptr >> (*b).endbit) & 1) as libc::c_long;
    (*b).endbit += 1;
    if (*b).endbit > 7 {
        (*b).endbit = 0;
        (*b).ptr = (*b).ptr.add(1);
        (*b).endbyte += 1;
    }
    return ret;
    unsafe fn goto_overflow(b: *mut oggpack_buffer) {
        (*b).ptr = std::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
    }
}
