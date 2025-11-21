pub unsafe fn ogg_page_packets(og: *const ogg_page) -> libc::c_int {
    let header = (*og).header;
    let n: libc::c_int = *header.add(26) as libc::c_int;
    let mut count: libc::c_int = 0;
    let mut i: libc::c_int = 0;
    while i < n {
        if *header.add(27usize + i as usize) < 255u8 {
            count += 1;
        }
        i += 1;
    }
    count
}
