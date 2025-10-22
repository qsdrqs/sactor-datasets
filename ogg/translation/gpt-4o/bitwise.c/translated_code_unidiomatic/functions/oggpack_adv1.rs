pub unsafe fn oggpack_adv1(b: *mut oggpack_buffer) {
    if !b.is_null() {
        (*b).endbit += 1;
        if (*b).endbit > 7 {
            (*b).endbit = 0;
            (*b).ptr = (*b).ptr.add(1);
            (*b).endbyte += 1;
        }
    }
}
