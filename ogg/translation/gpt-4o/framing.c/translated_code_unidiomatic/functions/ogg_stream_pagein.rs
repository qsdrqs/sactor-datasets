use libc::{c_int, c_long, c_uchar, memcpy, memmove};
pub unsafe fn ogg_stream_pagein(os: *mut ogg_stream_state, og: *mut ogg_page) -> c_int {
    let header = (*og).header;
    let mut body = (*og).body;
    let mut bodysize = (*og).body_len;
    let mut segptr = 0;
    let version = ogg_page_version(og);
    let continued = ogg_page_continued(og);
    let mut bos = ogg_page_bos(og);
    let eos = ogg_page_eos(og);
    let granulepos = ogg_page_granulepos(og);
    let serialno = ogg_page_serialno(og);
    let pageno = ogg_page_pageno(og);
    let segments = *header.offset(26) as c_int;
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    {
        let lr = (*os).lacing_returned;
        let br = (*os).body_returned;
        if br != 0 {
            (*os).body_fill -= br;
            if (*os).body_fill != 0 {
                memmove(
                    (*os).body_data as *mut libc::c_void,
                    (*os).body_data.offset(br as isize) as *const libc::c_void,
                    (*os).body_fill as usize,
                );
            }
            (*os).body_returned = 0;
        }
        if lr != 0 {
            if (*os).lacing_fill - lr != 0 {
                memmove(
                    (*os).lacing_vals as *mut libc::c_void,
                    (*os).lacing_vals.offset(lr as isize) as *const libc::c_void,
                    ((*os).lacing_fill - lr) as usize * std::mem::size_of::<c_int>(),
                );
                memmove(
                    (*os).granule_vals as *mut libc::c_void,
                    (*os).granule_vals.offset(lr as isize) as *const libc::c_void,
                    ((*os).lacing_fill - lr) as usize * std::mem::size_of::<c_long>(),
                );
            }
            (*os).lacing_fill -= lr;
            (*os).lacing_packet -= lr;
            (*os).lacing_returned = 0;
        }
    }
    if serialno != (*os).serialno as i32 {
        return -1;
    }
    if version > 0 {
        return -1;
    }
    if _os_lacing_expand(os, segments as c_long + 1) != 0 {
        return -1;
    }
    if pageno != (*os).pageno {
        for i in (*os).lacing_packet..(*os).lacing_fill {
            (*os).body_fill -= (*(*os).lacing_vals.offset(i as isize) & 0xff) as c_long;
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
            || (*(*os).lacing_vals.offset((*os).lacing_fill as isize - 1) & 0xff) < 255
            || *(*os).lacing_vals.offset((*os).lacing_fill as isize - 1) == 0x400
        {
            bos = 0;
            while segptr < segments {
                let val = *header.offset(27 + segptr as isize) as c_int;
                body = body.offset(val as isize);
                bodysize -= val as c_long;
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
        memcpy(
            (*os).body_data.offset((*os).body_fill as isize) as *mut libc::c_void,
            body as *const libc::c_void,
            bodysize as usize,
        );
        (*os).body_fill += bodysize;
    }
    {
        let mut saved = -1;
        while segptr < segments {
            let val = *header.offset(27 + segptr as isize) as c_int;
            *(*os).lacing_vals.offset((*os).lacing_fill as isize) = val;
            *(*os).granule_vals.offset((*os).lacing_fill as isize) = -1;
            if bos != 0 {
                *(*os).lacing_vals.offset((*os).lacing_fill as isize) |= 0x100;
                bos = 0;
            }
            if val < 255 {
                saved = (*os).lacing_fill;
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
            *(*os).lacing_vals.offset((*os).lacing_fill as isize - 1) |= 0x200;
        }
    }
    (*os).pageno = pageno + 1;
    0
}
