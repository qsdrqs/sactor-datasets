pub fn oggpack_adv1(b: &mut OggPackBuffer<'_>) {
    b.endbit += 1;
    if b.endbit > 7 {
        b.endbit = 0;
        b.ptr += 1;
        b.endbyte += 1;
    }
}
