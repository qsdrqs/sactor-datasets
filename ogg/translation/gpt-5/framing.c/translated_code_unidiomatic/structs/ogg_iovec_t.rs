#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_iovec_t {
    pub iov_base: *mut libc::c_void,
    pub iov_len: libc::c_ulong,
}
