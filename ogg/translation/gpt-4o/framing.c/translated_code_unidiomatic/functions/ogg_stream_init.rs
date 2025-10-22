use libc::{c_int, c_long, c_uchar, malloc, memset, size_t};
pub unsafe fn ogg_stream_init(os: *mut ogg_stream_state, serialno: c_int) -> c_int {
    if !os.is_null() {
        memset(
            os as *mut libc::c_void,
            0,
            std::mem::size_of::<ogg_stream_state>() as size_t,
        );
        (*os).body_storage = 16 * 1024;
        (*os).lacing_storage = 1024;
        (*os).body_data =
            malloc((*os).body_storage as size_t * std::mem::size_of::<c_uchar>()) as *mut c_uchar;
        (*os).lacing_vals =
            malloc((*os).lacing_storage as size_t * std::mem::size_of::<c_int>()) as *mut c_int;
        (*os).granule_vals =
            malloc((*os).lacing_storage as size_t * std::mem::size_of::<c_long>()) as *mut c_long;
        if (*os).body_data.is_null() || (*os).lacing_vals.is_null() || (*os).granule_vals.is_null()
        {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).serialno = serialno as c_long;
        return 0;
    }
    -1
}
