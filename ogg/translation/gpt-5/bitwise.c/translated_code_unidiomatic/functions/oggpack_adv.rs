pub unsafe fn oggpack_adv(b: *mut oggpack_buffer, mut bits: libc::c_int) {
    let b_ref = &mut *b;
    bits += b_ref.endbit;
    let needed_bytes = ((bits + 7) >> 3) as libc::c_long;
    if b_ref.endbyte > b_ref.storage - needed_bytes {
        b_ref.ptr = core::ptr::null_mut();
        b_ref.endbyte = b_ref.storage;
        b_ref.endbit = 1 as libc::c_int;
        return;
    }
    let byte_incr_int = bits / 8;
    b_ref.ptr = b_ref.ptr.offset(byte_incr_int as isize);
    b_ref.endbyte += byte_incr_int as libc::c_long;
    b_ref.endbit = bits & 7;
}
