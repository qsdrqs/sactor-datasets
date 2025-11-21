pub unsafe fn oggpack_look1(b: *mut oggpack_buffer) -> libc::c_long {
    if (*b).endbyte >= (*b).storage {
        return -1;
    }
    return ((*(*b).ptr >> (*b).endbit) & 1) as libc::c_long;
}
