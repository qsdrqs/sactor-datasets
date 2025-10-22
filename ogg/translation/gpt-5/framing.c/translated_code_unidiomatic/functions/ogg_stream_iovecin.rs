pub unsafe fn ogg_stream_iovecin(
    os: *mut ogg_stream_state,
    iov: *mut ogg_iovec_t,
    count: libc::c_int,
    e_o_s: libc::c_long,
    granulepos: libc::c_long,
) -> libc::c_int {
    let mut bytes: libc::c_long = 0;
    let mut lacing_vals: libc::c_long;
    let long_max = libc::c_long::MAX as libc::c_ulong;
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    if iov.is_null() {
        return 0;
    }
    for i in 0..(count as usize) {
        let elem = *iov.add(i);
        if elem.iov_len > long_max {
            return -1;
        }
        let len_l = elem.iov_len as libc::c_long;
        if bytes > libc::c_long::MAX - len_l {
            return -1;
        }
        bytes += len_l;
    }
    lacing_vals = bytes / (255 as libc::c_long) + 1;
    if (*os).body_returned != 0 {
        (*os).body_fill -= (*os).body_returned;
        if (*os).body_fill != 0 {
            libc::memmove(
                (*os).body_data as *mut libc::c_void,
                (*os).body_data.add((*os).body_returned as usize) as *const libc::c_void,
                (*os).body_fill as usize,
            );
        }
        (*os).body_returned = 0;
    }
    if _os_body_expand(os, bytes) != 0 || _os_lacing_expand(os, lacing_vals) != 0 {
        return -1;
    }
    for i in 0..(count as usize) {
        let elem = *iov.add(i);
        libc::memcpy(
            (*os).body_data.add((*os).body_fill as usize) as *mut libc::c_void,
            elem.iov_base as *const libc::c_void,
            elem.iov_len as usize,
        );
        (*os).body_fill += (elem.iov_len as libc::c_int) as libc::c_long;
    }
    for i in 0..((lacing_vals - 1) as usize) {
        let idx = (*os).lacing_fill as usize + i;
        *(*os).lacing_vals.add(idx) = 255;
        *(*os).granule_vals.add(idx) = (*os).granulepos;
    }
    let last_idx = (*os).lacing_fill + (lacing_vals - 1);
    *(*os).lacing_vals.add(last_idx as usize) = (bytes % (255 as libc::c_long)) as libc::c_int;
    (*os).granulepos = granulepos;
    *(*os).granule_vals.add(last_idx as usize) = granulepos;
    let first_idx = (*os).lacing_fill as usize;
    *(*os).lacing_vals.add(first_idx) |= 0x100;
    (*os).lacing_fill += lacing_vals;
    (*os).packetno += 1;
    if e_o_s != 0 {
        (*os).e_o_s = 1;
    }
    0
}
