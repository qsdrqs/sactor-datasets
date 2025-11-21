use libc::{c_int, c_long, c_void, memcpy, memmove, size_t};
pub unsafe fn ogg_stream_iovecin(
    os: *mut ogg_stream_state,
    iov: *mut ogg_iovec_t,
    count: c_int,
    e_o_s: c_long,
    granulepos: c_long,
) -> c_int {
    let mut bytes: c_long = 0;
    let mut lacing_vals: c_long;
    let mut i: c_int;
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    if iov.is_null() {
        return 0;
    }
    for i in 0..count {
        let iov_len = (*iov.add(i as usize)).iov_len;
        if iov_len > std::i64::MAX as size_t {
            return -1;
        }
        if bytes > std::i64::MAX - iov_len as c_long {
            return -1;
        }
        bytes += iov_len as c_long;
    }
    lacing_vals = bytes / 255 + 1;
    if (*os).body_returned != 0 {
        (*os).body_fill -= (*os).body_returned;
        if (*os).body_fill != 0 {
            memmove(
                (*os).body_data as *mut c_void,
                (*os).body_data.add((*os).body_returned as usize) as *const c_void,
                (*os).body_fill as usize,
            );
        }
        (*os).body_returned = 0;
    }
    if _os_body_expand(os, bytes) != 0 || _os_lacing_expand(os, lacing_vals) != 0 {
        return -1;
    }
    for i in 0..count {
        let iov_base = (*iov.add(i as usize)).iov_base;
        let iov_len = (*iov.add(i as usize)).iov_len;
        memcpy(
            (*os).body_data.add((*os).body_fill as usize) as *mut c_void,
            iov_base,
            iov_len,
        );
        (*os).body_fill += iov_len as c_long;
    }
    for i in 0..lacing_vals - 1 {
        *(*os)
            .lacing_vals
            .add((*os).lacing_fill as usize + i as usize) = 255;
        *(*os)
            .granule_vals
            .add((*os).lacing_fill as usize + i as usize) = (*os).granulepos;
    }
    *(*os)
        .lacing_vals
        .add((*os).lacing_fill as usize + (lacing_vals - 1) as usize) = (bytes % 255) as c_int;
    (*os).granulepos = granulepos;
    *(*os)
        .granule_vals
        .add((*os).lacing_fill as usize + (lacing_vals - 1) as usize) = granulepos;
    *(*os).lacing_vals.add((*os).lacing_fill as usize) |= 0x100;
    (*os).lacing_fill += lacing_vals;
    (*os).packetno += 1;
    if e_o_s != 0 {
        (*os).e_o_s = 1;
    }
    0
}
