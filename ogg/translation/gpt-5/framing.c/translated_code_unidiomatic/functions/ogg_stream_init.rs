pub unsafe fn ogg_stream_init(os: *mut ogg_stream_state, serialno: libc::c_int) -> libc::c_int {
    if os.is_null() {
        return -1;
    }
    libc::memset(
        os as *mut libc::c_void,
        0,
        core::mem::size_of::<ogg_stream_state>(),
    );
    let os_ref = &mut *os;
    os_ref.body_storage = (16 * 1024) as libc::c_long;
    os_ref.lacing_storage = 1024 as libc::c_long;
    os_ref.body_data =
        libc::malloc((os_ref.body_storage as usize) * core::mem::size_of::<libc::c_uchar>())
            as *mut libc::c_uchar;
    os_ref.lacing_vals =
        libc::malloc((os_ref.lacing_storage as usize) * core::mem::size_of::<libc::c_int>())
            as *mut libc::c_int;
    os_ref.granule_vals =
        libc::malloc((os_ref.lacing_storage as usize) * core::mem::size_of::<libc::c_long>())
            as *mut libc::c_long;
    if os_ref.body_data.is_null() || os_ref.lacing_vals.is_null() || os_ref.granule_vals.is_null() {
        ogg_stream_clear(os);
        return -1;
    }
    os_ref.serialno = serialno as libc::c_long;
    0
}
