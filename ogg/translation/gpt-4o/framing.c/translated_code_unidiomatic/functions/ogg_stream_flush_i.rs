pub unsafe fn ogg_stream_flush_i(
    os: *mut ogg_stream_state,
    og: *mut ogg_page,
    mut force: libc::c_int,
    nfill: libc::c_int,
) -> libc::c_int {
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
        for v in 0..maxvals {
            if (*(*os).lacing_vals.offset(v as isize) & 0x0ff) < 255 {
                vals = v + 1;
                break;
            }
        }
    } else {
        let mut packets_done: libc::c_int = 0;
        let mut packet_just_done: libc::c_int = 0;
        for v in 0..maxvals {
            if acc > nfill as libc::c_long && packet_just_done >= 4 {
                force = 1;
                break;
            }
            acc += (*(*os).lacing_vals.offset(v as isize) & 0x0ff) as libc::c_long;
            if (*(*os).lacing_vals.offset(v as isize) & 0xff) < 255 {
                granule_pos = *(*os).granule_vals.offset(v as isize);
                packet_just_done = packets_done + 1;
                packets_done = packet_just_done;
            } else {
                packet_just_done = 0;
            }
            vals = v + 1;
        }
        if vals == 255 {
            force = 1;
        }
    }
    if force == 0 {
        return 0;
    }
    libc::memcpy(
        (*os).header.as_mut_ptr() as *mut libc::c_void,
        b"OggS\0".as_ptr() as *const libc::c_void,
        4,
    );
    (*os).header[4] = 0x00;
    (*os).header[5] = 0x00;
    if (*(*os).lacing_vals.offset(0) & 0x100) == 0 {
        (*os).header[5] |= 0x01;
    }
    if (*os).b_o_s == 0 {
        (*os).header[5] |= 0x02;
    }
    if (*os).e_o_s != 0 && (*os).lacing_fill == vals as libc::c_long {
        (*os).header[5] |= 0x04;
    }
    (*os).b_o_s = 1;
    for i in 6..14 {
        (*os).header[i] = (granule_pos & 0xff) as libc::c_uchar;
        granule_pos >>= 8;
    }
    let mut serialno = (*os).serialno;
    for i in 14..18 {
        (*os).header[i] = (serialno & 0xff) as libc::c_uchar;
        serialno >>= 8;
    }
    if (*os).pageno == -1 {
        (*os).pageno = 0;
    }
    let mut pageno = (*os).pageno;
    (*os).pageno += 1;
    for i in 18..22 {
        (*os).header[i] = (pageno & 0xff) as libc::c_uchar;
        pageno >>= 8;
    }
    (*os).header[22] = 0;
    (*os).header[23] = 0;
    (*os).header[24] = 0;
    (*os).header[25] = 0;
    (*os).header[26] = (vals & 0xff) as libc::c_uchar;
    for i in 0..vals {
        bytes += {
            let val = (*(*os).lacing_vals.offset(i as isize) & 0xff) as libc::c_uchar;
            (*os).header[i as usize + 27] = val;
            val as libc::c_int
        };
    }
    (*og).header = (*os).header.as_mut_ptr();
    (*og).header_len = (vals + 27) as libc::c_long;
    (*os).header_fill = (vals + 27) as libc::c_int;
    (*og).body = (*os).body_data.offset((*os).body_returned as isize);
    (*og).body_len = bytes as libc::c_long;
    (*os).lacing_fill -= vals as libc::c_long;
    libc::memmove(
        (*os).lacing_vals as *mut libc::c_void,
        (*os).lacing_vals.offset(vals as isize) as *const libc::c_void,
        ((*os).lacing_fill as usize) * std::mem::size_of::<libc::c_int>(),
    );
    libc::memmove(
        (*os).granule_vals as *mut libc::c_void,
        (*os).granule_vals.offset(vals as isize) as *const libc::c_void,
        ((*os).lacing_fill as usize) * std::mem::size_of::<libc::c_long>(),
    );
    (*os).body_returned += bytes as libc::c_long;
    ogg_page_checksum_set(og);
    1
}
