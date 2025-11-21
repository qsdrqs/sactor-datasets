pub unsafe fn ogg_stream_pagein(os: *mut ogg_stream_state, og: *mut ogg_page) -> libc::c_int {
    let mut header = (*og).header;
    let mut body = (*og).body;
    let mut bodysize: libc::c_long = (*og).body_len;
    let mut segptr: libc::c_int = 0;
    let mut version: libc::c_int = ogg_page_version(og as *const ogg_page);
    let mut continued: libc::c_int = ogg_page_continued(og as *const ogg_page);
    let mut bos: libc::c_int = ogg_page_bos(og as *const ogg_page);
    let mut eos: libc::c_int = ogg_page_eos(og as *const ogg_page);
    let mut granulepos: libc::c_long = ogg_page_granulepos(og as *const ogg_page);
    let mut serialno: libc::c_int = ogg_page_serialno(og as *const ogg_page);
    let mut pageno: libc::c_long = ogg_page_pageno(og as *const ogg_page);
    let mut segments: libc::c_int = *header.offset(26) as libc::c_int;
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    {
        let lr: libc::c_long = (*os).lacing_returned;
        let br: libc::c_long = (*os).body_returned;
        if br != 0 {
            (*os).body_fill -= br;
            if (*os).body_fill != 0 {
                libc::memmove(
                    (*os).body_data as *mut libc::c_void,
                    (*os).body_data.offset(br as isize) as *const libc::c_void,
                    (*os).body_fill as usize,
                );
            }
            (*os).body_returned = 0;
        }
        if lr != 0 {
            let rem: libc::c_long = (*os).lacing_fill - lr;
            if rem != 0 {
                libc::memmove(
                    (*os).lacing_vals as *mut libc::c_void,
                    (*os).lacing_vals.offset(lr as isize) as *const libc::c_void,
                    (rem as usize) * core::mem::size_of::<libc::c_int>(),
                );
                libc::memmove(
                    (*os).granule_vals as *mut libc::c_void,
                    (*os).granule_vals.offset(lr as isize) as *const libc::c_void,
                    (rem as usize) * core::mem::size_of::<libc::c_long>(),
                );
            }
            (*os).lacing_fill -= lr;
            (*os).lacing_packet -= lr;
            (*os).lacing_returned = 0;
        }
    }
    if (serialno as libc::c_long) != (*os).serialno {
        return -1;
    }
    if version > 0 {
        return -1;
    }
    if _os_lacing_expand(os, (segments as libc::c_long) + 1) != 0 {
        return -1;
    }
    if pageno != (*os).pageno {
        let mut i: libc::c_int = (*os).lacing_packet as libc::c_int;
        while i < (*os).lacing_fill as libc::c_int {
            let v = *(*os).lacing_vals.offset(i as isize) & 0xff;
            (*os).body_fill -= v as libc::c_long;
            i += 1;
        }
        (*os).lacing_fill = (*os).lacing_packet;
        if (*os).pageno != -1 {
            *(*os).lacing_vals.offset((*os).lacing_fill as isize) = 0x400;
            (*os).lacing_fill += 1;
            (*os).lacing_packet += 1;
        }
    }
    if continued != 0 {
        if (*os).lacing_fill < 1
            || ((*(*os).lacing_vals.offset((*os).lacing_fill as isize - 1)) & 0xff) < 255
            || *(*os).lacing_vals.offset((*os).lacing_fill as isize - 1) == 0x400
        {
            bos = 0;
            while segptr < segments {
                let val: libc::c_int = *header.offset(27 + segptr as isize) as libc::c_int;
                body = body.offset(val as isize);
                bodysize -= val as libc::c_long;
                if val < 255 {
                    segptr += 1;
                    break;
                }
                segptr += 1;
            }
        }
    }
    if bodysize != 0 {
        if _os_body_expand(os, bodysize) != 0 {
            return -1;
        }
        libc::memcpy(
            (*os).body_data.offset((*os).body_fill as isize) as *mut libc::c_void,
            body as *const libc::c_void,
            bodysize as usize,
        );
        (*os).body_fill += bodysize;
    }
    {
        let mut saved: libc::c_int = -1;
        while segptr < segments {
            let val: libc::c_int = *header.offset(27 + segptr as isize) as libc::c_int;
            *(*os).lacing_vals.offset((*os).lacing_fill as isize) = val;
            *(*os).granule_vals.offset((*os).lacing_fill as isize) = -1;
            if bos != 0 {
                let p = (*os).lacing_vals.offset((*os).lacing_fill as isize);
                *p |= 0x100;
                bos = 0;
            }
            if val < 255 {
                saved = (*os).lacing_fill as libc::c_int;
            }
            (*os).lacing_fill += 1;
            segptr += 1;
            if val < 255 {
                (*os).lacing_packet = (*os).lacing_fill;
            }
        }
        if saved != -1 {
            *(*os).granule_vals.offset(saved as isize) = granulepos;
        }
    }
    if eos != 0 {
        (*os).e_o_s = 1;
        if (*os).lacing_fill > 0 {
            let idx = (*os).lacing_fill as isize - 1;
            *(*os).lacing_vals.offset(idx) |= 0x200;
        }
    }
    (*os).pageno = pageno + 1;
    0
}
