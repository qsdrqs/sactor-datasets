pub unsafe fn oggpack_reset(b: *mut oggpack_buffer) {
    if (*b).ptr.is_null() {
        return;
    }
    (*b).ptr = (*b).buffer;
    *(*b).buffer = 0 as libc::c_uchar;
    (*b).endbyte = 0 as libc::c_long;
    (*b).endbit = (*b).endbyte as libc::c_int;
}
