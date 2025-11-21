#[no_mangle]
pub unsafe fn oggpack_adv1(b: *mut oggpack_buffer) {
    let b = &mut *b;
    b.endbit += 1;
    if b.endbit > 7 {
        b.endbit = 0;
        b.ptr = b.ptr.offset(1);
        b.endbyte += 1 as libc::c_long;
    }
}
