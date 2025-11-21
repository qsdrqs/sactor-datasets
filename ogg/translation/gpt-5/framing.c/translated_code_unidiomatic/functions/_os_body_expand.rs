pub unsafe fn _os_body_expand(os: *mut ogg_stream_state, needed: libc::c_long) -> libc::c_int {
    if os.is_null() {
        return -1;
    }
    let os_ref = &mut *os;
    let long_bits = (8 * core::mem::size_of::<libc::c_long>()) as u32;
    let long_max_i128: i128 = (1_i128 << (long_bits - 1)) - 1_i128;
    let lhs = (os_ref.body_storage as i128) - (needed as i128);
    let rhs = os_ref.body_fill as i128;
    if lhs <= rhs {
        if (os_ref.body_storage as i128) > (long_max_i128 - (needed as i128)) {
            ogg_stream_clear(os);
            return -1;
        }
        let mut body_storage_i128 = (os_ref.body_storage as i128) + (needed as i128);
        if body_storage_i128 < (long_max_i128 - 1024_i128) {
            body_storage_i128 += 1024_i128;
        }
        let body_storage = body_storage_i128 as libc::c_long;
        let size = (body_storage as usize) * core::mem::size_of::<libc::c_uchar>();
        let ret = libc::realloc(os_ref.body_data as *mut libc::c_void, size) as *mut libc::c_uchar;
        if ret.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        os_ref.body_storage = body_storage;
        os_ref.body_data = ret;
    }
    0
}
