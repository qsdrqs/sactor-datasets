pub fn oggpackB_readinit<'a>(buf: &'a mut [u8]) -> OggPackBuffer<'a> {
    oggpack_readinit(buf)
}
