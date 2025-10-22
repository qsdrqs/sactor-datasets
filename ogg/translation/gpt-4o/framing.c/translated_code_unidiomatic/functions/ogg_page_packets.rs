use libc;
pub unsafe fn ogg_page_packets(og: *const ogg_page) -> i32 {
    let mut n = *(*og).header.offset(26) as i32;
    let mut count = 0;
    for i in 0..n {
        if *(*og).header.offset(27 + i as isize) < 255 {
            count += 1;
        }
    }
    count
}
