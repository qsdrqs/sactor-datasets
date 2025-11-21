pub unsafe fn oggpackB_writetrunc(b: *mut oggpack_buffer, mut bits: libc::c_long) {
    let bytes = bits >> 3;
    if !(*b).ptr.is_null() {
        bits -= bytes * 8;
        (*b).ptr = (*b).buffer.offset(bytes as isize);
        (*b).endbit = bits as libc::c_int;
        (*b).endbyte = bytes;
        let mask = mask8B[bits as usize] as libc::c_uchar;
        let p = (*b).ptr;
        *p = (*p) & mask;
    }
}
