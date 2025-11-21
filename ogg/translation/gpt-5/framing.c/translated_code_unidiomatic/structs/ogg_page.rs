#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_page {
    pub header: *mut libc::c_uchar,
    pub header_len: libc::c_long,
    pub body: *mut libc::c_uchar,
    pub body_len: libc::c_long,
}
