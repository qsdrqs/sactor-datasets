#[no_mangle]
pub unsafe fn oggpack_writetrunc(b: *mut oggpack_buffer, bits: libc::c_long) {
    let mut bits_ = bits;
    let bytes: libc::c_long = bits_ >> 3;
    if !(*b).ptr.is_null() {
        bits_ -= bytes * 8;
        (*b).ptr = (*b).buffer.offset(bytes as isize);
        (*b).endbit = bits_ as libc::c_int;
        (*b).endbyte = bytes;
        let m: libc::c_uchar = mask[bits_ as usize] as libc::c_uchar;
        let p = (*b).ptr;
        *p = *p & m;
    }
}
