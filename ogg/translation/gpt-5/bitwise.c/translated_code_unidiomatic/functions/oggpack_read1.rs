pub unsafe fn oggpack_read1(b: *mut oggpack_buffer) -> libc::c_long {
    if (*b).endbyte >= (*b).storage {
        (*b).ptr = core::ptr::null_mut();
        (*b).endbyte = (*b).storage;
        (*b).endbit = 1;
        return -1 as libc::c_long;
    }
    let ret: libc::c_long = (((*(*b).ptr) as libc::c_int >> (*b).endbit) & 1) as libc::c_long;
    (*b).endbit += 1;
    if (*b).endbit > 7 {
        (*b).endbit = 0;
        (*b).ptr = (*b).ptr.offset(1);
        (*b).endbyte += 1;
    }
    ret
}
