#[no_mangle]
pub unsafe fn ogg_stream_clear(os: *mut ogg_stream_state) -> libc::c_int {
    if !os.is_null() {
        let body_data = (*os).body_data;
        if !body_data.is_null() {
            libc::free(body_data as *mut libc::c_void);
        }
        let lacing_vals = (*os).lacing_vals;
        if !lacing_vals.is_null() {
            libc::free(lacing_vals as *mut libc::c_void);
        }
        let granule_vals = (*os).granule_vals;
        if !granule_vals.is_null() {
            libc::free(granule_vals as *mut libc::c_void);
        }
        libc::memset(
            os as *mut libc::c_void,
            0,
            core::mem::size_of::<ogg_stream_state>() as libc::size_t,
        );
    }
    0
}
