use libc::{c_int, c_long, c_uchar, free, memset};
pub unsafe fn ogg_stream_clear(os: *mut ogg_stream_state) -> c_int {
    if !os.is_null() {
        if !(*os).body_data.is_null() {
            free((*os).body_data as *mut libc::c_void);
        }
        if !(*os).lacing_vals.is_null() {
            free((*os).lacing_vals as *mut libc::c_void);
        }
        if !(*os).granule_vals.is_null() {
            free((*os).granule_vals as *mut libc::c_void);
        }
        memset(
            os as *mut libc::c_void,
            0,
            std::mem::size_of::<ogg_stream_state>(),
        );
    }
    0
}
