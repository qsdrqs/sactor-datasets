#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_sync_state {
    pub data: *mut libc::c_uchar,
    pub storage: libc::c_int,
    pub fill: libc::c_int,
    pub returned: libc::c_int,
    pub unsynced: libc::c_int,
    pub headerbytes: libc::c_int,
    pub bodybytes: libc::c_int,
}
