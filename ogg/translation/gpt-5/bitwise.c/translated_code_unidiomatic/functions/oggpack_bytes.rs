pub fn oggpack_bytes(b: *mut oggpack_buffer) -> libc::c_long {
    unsafe { (*b).endbyte + (((*b).endbit + 7) / 8) as libc::c_long }
}
