use libc::{c_int, c_long, c_uchar};
pub unsafe fn oggpackB_writealign(b: *mut oggpack_buffer) {
    let bits: c_int = 8 - (*b).endbit;
    if bits < 8 {
        oggpackB_write(b, 0, bits);
    }
}
