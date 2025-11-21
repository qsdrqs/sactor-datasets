#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_packet {
    pub packet: *mut libc::c_uchar,
    pub bytes: libc::c_long,
    pub b_o_s: libc::c_long,
    pub e_o_s: libc::c_long,
    pub granulepos: libc::c_long,
    pub packetno: libc::c_long,
}
