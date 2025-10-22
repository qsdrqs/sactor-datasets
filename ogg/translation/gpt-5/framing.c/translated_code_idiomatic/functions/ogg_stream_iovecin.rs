pub fn ogg_stream_iovecin<'a>(
    os: &mut OggStreamState<'a>,
    iov: Option<&[OggIovec<'_>]>,
    e_o_s: bool,
    granulepos: i64,
) -> i32 {
    if ogg_stream_check(Some(os)) != 0 {
        return -1;
    }
    let iov = match iov {
        None => return 0,
        Some(v) if v.is_empty() => return 0,
        Some(v) => v,
    };
    let mut total_bytes: usize = 0;
    for elem in iov {
        total_bytes = match total_bytes.checked_add(elem.iov_base.len()) {
            Some(sum) => sum,
            None => return -1,
        };
    }
    if total_bytes > isize::MAX as usize {
        return -1;
    }
    let full_segments = total_bytes / 255;
    let lacing_needed = full_segments + 1;
    if os.body_returned != 0 {
        let new_fill = os.body_fill.saturating_sub(os.body_returned);
        if new_fill != 0 {
            os.body_data
                .copy_within(os.body_returned..os.body_returned + new_fill, 0);
        }
        os.body_fill = new_fill;
        os.body_returned = 0;
    }
    if _os_body_expand(os, total_bytes as isize) != 0 || _os_lacing_expand(os, lacing_needed) != 0 {
        return -1;
    }
    {
        let mut fill = os.body_fill;
        for elem in iov {
            let src = elem.iov_base;
            os.body_data[fill..fill + src.len()].copy_from_slice(src);
            fill += src.len();
        }
        os.body_fill = fill;
    }
    {
        let start = os.lacing_fill;
        let prior_granule = os.granulepos;
        for i in 0..full_segments {
            os.lacing_vals[start + i] = 255;
            os.granule_vals[start + i] = prior_granule;
        }
        let last_idx = start + lacing_needed - 1;
        let remainder = (total_bytes - full_segments * 255) as i32;
        os.lacing_vals[last_idx] = remainder;
        os.granulepos = granulepos;
        os.granule_vals[last_idx] = granulepos;
        os.lacing_vals[start] |= 0x100;
        os.lacing_fill = start + lacing_needed;
        os.packetno = os.packetno.wrapping_add(1);
    }
    if e_o_s {
        os.e_o_s = true;
    }
    if os.pageno == u32::MAX {
        os.pageno = 0;
    }
    0
}
