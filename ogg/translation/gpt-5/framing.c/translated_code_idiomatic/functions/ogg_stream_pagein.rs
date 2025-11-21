pub fn ogg_stream_pagein<'a>(os: &mut OggStreamState<'a>, og: &OggPage<'_>) -> i32 {
    if ogg_stream_check(Some(&*os)) != 0 {
        return -1;
    }
    let version = ogg_page_version(og);
    let mut bos = ogg_page_bos(og);
    let eos = ogg_page_eos(og);
    let continued = ogg_page_continued(og);
    let granulepos = ogg_page_granulepos(og);
    let serialno = ogg_page_serialno(og) as u32;
    let pageno = ogg_page_pageno(og);
    let segments = match og.header.get(26) {
        Some(&b) => b as usize,
        None => return -1,
    };
    if serialno != os.serialno {
        return -1;
    }
    if version > 0 {
        return -1;
    }
    {
        let lr = os.lacing_returned;
        let br = os.body_returned;
        if br != 0 {
            os.body_fill = os.body_fill.saturating_sub(br);
            if os.body_fill != 0 {
                let from_start = br;
                let from_end = br.saturating_add(os.body_fill);
                if from_end <= os.body_data.len() {
                    os.body_data.copy_within(from_start..from_end, 0);
                } else {
                    let available = os.body_data.len().saturating_sub(br);
                    os.body_data
                        .copy_within(from_start..(from_start + available), 0);
                    os.body_fill = available;
                }
            }
            os.body_returned = 0;
        }
        if lr != 0 {
            let rem = os.lacing_fill.saturating_sub(lr);
            if rem != 0 {
                let from_start = lr;
                let from_end = lr.saturating_add(rem);
                if from_end <= os.lacing_vals.len() {
                    os.lacing_vals.copy_within(from_start..from_end, 0);
                } else {
                    let available = os.lacing_vals.len().saturating_sub(lr);
                    os.lacing_vals
                        .copy_within(from_start..(from_start + available), 0);
                }
                if from_end <= os.granule_vals.len() {
                    os.granule_vals.copy_within(from_start..from_end, 0);
                } else {
                    let available = os.granule_vals.len().saturating_sub(lr);
                    os.granule_vals
                        .copy_within(from_start..(from_start + available), 0);
                }
            }
            os.lacing_fill = os.lacing_fill.saturating_sub(lr);
            os.lacing_packet = os.lacing_packet.saturating_sub(lr);
            os.lacing_returned = 0;
        }
    }
    if _os_lacing_expand(os, segments + 1) != 0 {
        return -1;
    }
    if pageno != os.pageno {
        let mut i = os.lacing_packet;
        while i < os.lacing_fill {
            let v = (os.lacing_vals[i] & 0xff) as usize;
            os.body_fill = os.body_fill.saturating_sub(v);
            i += 1;
        }
        os.lacing_fill = os.lacing_packet;
        if os.pageno != u32::MAX {
            if os.lacing_fill >= os.lacing_vals.len() || os.lacing_fill >= os.granule_vals.len() {
                if _os_lacing_expand(os, os.lacing_fill + 1) != 0 {
                    return -1;
                }
            }
            os.lacing_vals[os.lacing_fill] = 0x400;
            os.lacing_fill += 1;
            os.lacing_packet += 1;
        }
    }
    let mut segptr: usize = 0;
    let mut body_off: usize = 0;
    let mut bodysize: usize = og.body.len();
    if continued != 0 {
        let needs_skip = os.lacing_fill < 1
            || (os.lacing_vals[os.lacing_fill - 1] & 0xff) < 255
            || os.lacing_vals[os.lacing_fill - 1] == 0x400;
        if needs_skip {
            bos = 0;
            while segptr < segments {
                let idx = 27 + segptr;
                let val = match og.header.get(idx) {
                    Some(&b) => b as usize,
                    None => return -1,
                };
                body_off = body_off.saturating_add(val);
                bodysize = bodysize.saturating_sub(val);
                segptr += 1;
                if val < 255 {
                    break;
                }
            }
        }
    }
    if bodysize != 0 {
        if _os_body_expand(os, bodysize as isize) != 0 {
            return -1;
        }
        let start = os.body_fill;
        let end = start.saturating_add(bodysize);
        if end <= os.body_data.len() && body_off.saturating_add(bodysize) <= og.body.len() {
            let src = &og.body[body_off..(body_off + bodysize)];
            let dst = &mut os.body_data[start..end];
            dst.copy_from_slice(src);
            os.body_fill = end;
        } else {
            return -1;
        }
    }
    {
        let mut saved: Option<usize> = None;
        while segptr < segments {
            let idx = 27 + segptr;
            let val_i32 = match og.header.get(idx) {
                Some(&b) => b as i32,
                None => return -1,
            };
            if os.lacing_fill >= os.lacing_vals.len() || os.lacing_fill >= os.granule_vals.len() {
                if _os_lacing_expand(os, os.lacing_fill + 1) != 0 {
                    return -1;
                }
            }
            os.lacing_vals[os.lacing_fill] = val_i32;
            os.granule_vals[os.lacing_fill] = -1;
            if bos != 0 {
                os.lacing_vals[os.lacing_fill] |= 0x100;
                bos = 0;
            }
            if val_i32 < 255 {
                saved = Some(os.lacing_fill);
            }
            os.lacing_fill += 1;
            segptr += 1;
            if val_i32 < 255 {
                os.lacing_packet = os.lacing_fill;
            }
        }
        if let Some(saved_idx) = saved {
            os.granule_vals[saved_idx] = granulepos;
        }
    }
    if eos != 0 {
        os.e_o_s = true;
        if os.lacing_fill > 0 {
            let idx = os.lacing_fill - 1;
            os.lacing_vals[idx] |= 0x200;
        }
    }
    os.pageno = pageno.wrapping_add(1);
    0
}
