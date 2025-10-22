pub fn ogg_page_checksum_set(og: &mut OggPage<'_>) {
    if og.header.len() < 26 {
        return;
    }
    {
        let header = &mut og.header;
        header[22..26].fill(0);
    }
    let crc = {
        let crc0 = _os_update_crc(0, &og.header);
        _os_update_crc(crc0, &og.body)
    };
    {
        let header = &mut og.header;
        let bytes = crc.to_le_bytes();
        header[22..26].copy_from_slice(&bytes);
    }
}
