pub unsafe fn ogg_stream_flush_i(
    os: *mut ogg_stream_state,
    og: *mut ogg_page,
    mut force: libc::c_int,
    nfill: libc::c_int,
) -> libc::c_int {
    let mut i: libc::c_int;
    let mut vals: libc::c_int = 0;
    let maxvals: libc::c_int;
    let mut bytes: libc::c_int = 0;
    let mut acc: libc::c_long = 0;
    let mut granule_pos: libc::c_long = -1;
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    maxvals = if (*os).lacing_fill > 255 {
        255
    } else {
        (*os).lacing_fill as libc::c_int
    };
    if maxvals == 0 {
        return 0;
    }
    if (*os).b_o_s == 0 {
        granule_pos = 0;
        vals = 0;
        while vals < maxvals {
            let lv = *(*os).lacing_vals.offset(vals as isize);
            if (lv & 0x0ff) < 255 {
                vals += 1;
                break;
            }
            vals += 1;
        }
    } else {
        let mut packets_done: libc::c_int = 0;
        let mut packet_just_done: libc::c_int = 0;
        vals = 0;
        while vals < maxvals {
            if acc > nfill as libc::c_long && packet_just_done >= 4 {
                force = 1;
                break;
            }
            let lv = *(*os).lacing_vals.offset(vals as isize);
            acc += (lv & 0x0ff) as libc::c_long;
            if (lv & 0xff) < 255 {
                granule_pos = *(*os).granule_vals.offset(vals as isize);
                packets_done += 1;
                packet_just_done = packets_done;
            } else {
                packet_just_done = 0;
            }
            vals += 1;
        }
        if vals == 255 {
            force = 1;
        }
    }
    if force == 0 {
        return 0;
    }
    (*os).header[0] = b'O';
    (*os).header[1] = b'g';
    (*os).header[2] = b'g';
    (*os).header[3] = b'S';
    (*os).header[4] = 0x00;
    (*os).header[5] = 0x00;
    if ((*os).lacing_vals.read() & 0x100) == 0 {
        (*os).header[5] |= 0x01;
    }
    if (*os).b_o_s == 0 {
        (*os).header[5] |= 0x02;
    }
    if (*os).e_o_s != 0 && (*os).lacing_fill == vals as libc::c_long {
        (*os).header[5] |= 0x04;
    }
    (*os).b_o_s = 1;
    i = 6;
    while i < 14 {
        (*os).header[i as usize] = (granule_pos & 0xff) as libc::c_uchar;
        granule_pos >>= 8;
        i += 1;
    }
    let mut serialno: libc::c_long = (*os).serialno;
    i = 14;
    while i < 18 {
        (*os).header[i as usize] = (serialno & 0xff) as libc::c_uchar;
        serialno >>= 8;
        i += 1;
    }
    if (*os).pageno == -1 {
        (*os).pageno = 0;
    }
    let mut pageno: libc::c_long = (*os).pageno;
    (*os).pageno = (*os).pageno.wrapping_add(1);
    i = 18;
    while i < 22 {
        (*os).header[i as usize] = (pageno & 0xff) as libc::c_uchar;
        pageno >>= 8;
        i += 1;
    }
    (*os).header[22] = 0;
    (*os).header[23] = 0;
    (*os).header[24] = 0;
    (*os).header[25] = 0;
    (*os).header[26] = (vals & 0xff) as libc::c_uchar;
    i = 0;
    while i < vals {
        let v = (*(*os).lacing_vals.offset(i as isize) & 0xff) as libc::c_int;
        (*os).header[(i + 27) as usize] = v as libc::c_uchar;
        bytes += v;
        i += 1;
    }
    (*og).header = (*os).header.as_mut_ptr();
    let header_len_val = (vals + 27) as libc::c_int;
    (*os).header_fill = header_len_val;
    (*og).header_len = header_len_val as libc::c_long;
    (*og).body = (*os).body_data.offset((*os).body_returned as isize);
    (*og).body_len = bytes as libc::c_long;
    (*os).lacing_fill -= vals as libc::c_long;
    libc::memmove(
        (*os).lacing_vals as *mut libc::c_void,
        (*os).lacing_vals.offset(vals as isize) as *const libc::c_void,
        ((*os).lacing_fill as usize).wrapping_mul(core::mem::size_of::<libc::c_int>())
            as libc::size_t,
    );
    libc::memmove(
        (*os).granule_vals as *mut libc::c_void,
        (*os).granule_vals.offset(vals as isize) as *const libc::c_void,
        ((*os).lacing_fill as usize).wrapping_mul(core::mem::size_of::<libc::c_long>())
            as libc::size_t,
    );
    (*os).body_returned += bytes as libc::c_long;
    ogg_page_checksum_set(og);
    1
}
