#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_stream_state {
    pub body_data: *mut libc::c_uchar,
    pub body_storage: libc::c_long,
    pub body_fill: libc::c_long,
    pub body_returned: libc::c_long,
    pub lacing_vals: *mut libc::c_int,
    pub granule_vals: *mut libc::c_long,
    pub lacing_storage: libc::c_long,
    pub lacing_fill: libc::c_long,
    pub lacing_packet: libc::c_long,
    pub lacing_returned: libc::c_long,
    pub header: [libc::c_uchar; 282],
    pub header_fill: libc::c_int,
    pub e_o_s: libc::c_int,
    pub b_o_s: libc::c_int,
    pub serialno: libc::c_long,
    pub pageno: libc::c_long,
    pub packetno: libc::c_long,
    pub granulepos: libc::c_long,
}
