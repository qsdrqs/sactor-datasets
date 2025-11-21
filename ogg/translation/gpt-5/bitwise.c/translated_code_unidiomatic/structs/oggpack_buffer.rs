#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct oggpack_buffer {
    pub endbyte: libc::c_long,
    pub endbit: libc::c_int,
    pub buffer: *mut libc::c_uchar,
    pub ptr: *mut libc::c_uchar,
    pub storage: libc::c_long,
}
