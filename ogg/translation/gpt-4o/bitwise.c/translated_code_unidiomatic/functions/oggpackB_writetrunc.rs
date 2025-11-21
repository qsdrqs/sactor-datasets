pub unsafe fn oggpackB_writetrunc(b: *mut oggpack_buffer, bits: libc::c_long) {
    let mut bytes = bits >> 3;
    if !(*b).ptr.is_null() {
        let mut bits = bits - bytes * 8;
        (*b).ptr = (*b).buffer.offset(bytes as isize);
        (*b).endbit = bits as libc::c_int;
        (*b).endbyte = bytes;
        *(*b).ptr &= mask8B[bits as usize] as libc::c_uchar;
    }
}
