pub unsafe fn _packetout(
    os: *mut ogg_stream_state,
    op: *mut ogg_packet,
    adv: libc::c_int,
) -> libc::c_int {
    let mut ptr: libc::c_int = (*os).lacing_returned as libc::c_int;
    if (*os).lacing_packet <= ptr as libc::c_long {
        return 0;
    }
    let mut val: libc::c_int = *(*os).lacing_vals.offset(ptr as isize);
    if (val & 0x400) != 0 {
        (*os).lacing_returned += 1;
        (*os).packetno += 1;
        return -1;
    }
    if op.is_null() && adv == 0 {
        return 1;
    }
    let mut size: libc::c_int = val & 0xff;
    let mut bytes: libc::c_long = size as libc::c_long;
    let mut eos: libc::c_int = val & 0x200;
    let mut bos: libc::c_int = val & 0x100;
    while size == 255 {
        ptr += 1;
        val = *(*os).lacing_vals.offset(ptr as isize);
        size = val & 0xff;
        if (val & 0x200) != 0 {
            eos = 0x200;
        }
        bytes += size as libc::c_long;
    }
    if !op.is_null() {
        (*op).e_o_s = eos as libc::c_long;
        (*op).b_o_s = bos as libc::c_long;
        (*op).packet = (*os).body_data.offset((*os).body_returned as isize);
        (*op).packetno = (*os).packetno;
        (*op).granulepos = *(*os).granule_vals.offset(ptr as isize);
        (*op).bytes = bytes;
    }
    if adv != 0 {
        (*os).body_returned += bytes;
        (*os).lacing_returned = (ptr + 1) as libc::c_long;
        (*os).packetno += 1;
    }
    1
}
