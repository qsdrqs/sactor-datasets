pub unsafe fn oggpackB_read1(b: *mut oggpack_buffer) -> libc::c_long {
    fn overflow(b: *mut oggpack_buffer) -> libc::c_long {
        unsafe {
            (*b).ptr = std::ptr::null_mut();
            (*b).endbyte = (*b).storage;
            (*b).endbit = 1;
        }
        -1
    }
    if (*b).endbyte >= (*b).storage {
        overflow(b)
    } else {
        let ret = ((*(*b).ptr) >> (7 - (*b).endbit)) & 1;
        (*b).endbit += 1;
        if (*b).endbit > 7 {
            (*b).endbit = 0;
            (*b).ptr = (*b).ptr.add(1);
            (*b).endbyte += 1;
        }
        ret as libc::c_long
    }
}
