pub unsafe fn ogg_sync_pageseek(oy: *mut ogg_sync_state, og: *mut ogg_page) -> libc::c_long {
    let page: *mut libc::c_uchar;
    let mut next: *mut libc::c_uchar = std::ptr::null_mut();
    let mut bytes: libc::c_long;
    if ogg_sync_check(oy) != 0 {
        return 0;
    }
    page = (*oy).data.offset((*oy).returned as isize);
    bytes = (*oy).fill as libc::c_long - (*oy).returned as libc::c_long;
    if (*oy).headerbytes == 0 {
        let headerbytes: libc::c_int;
        if bytes < 27 {
            return 0;
        }
        if libc::memcmp(
            page as *const libc::c_void,
            b"OggS\0".as_ptr() as *const libc::c_void,
            4,
        ) != 0
        {
            (*oy).headerbytes = 0;
            (*oy).bodybytes = 0;
            next = libc::memchr(
                page.offset(1) as *const libc::c_void,
                b'O' as libc::c_int,
                (bytes - 1) as libc::size_t,
            ) as *mut libc::c_uchar;
            if next.is_null() {
                next = (*oy).data.offset((*oy).fill as isize);
            }
            (*oy).returned = next.offset_from((*oy).data) as libc::c_int;
            return -(next.offset_from(page) as libc::c_long);
        }
        headerbytes = *page.offset(26) as libc::c_int + 27;
        if bytes < headerbytes as libc::c_long {
            return 0;
        }
        for i in 0..*page.offset(26) as libc::c_int {
            (*oy).bodybytes += *page.offset(27 + i as isize) as libc::c_int;
        }
        (*oy).headerbytes = headerbytes;
    }
    if (*oy).bodybytes + (*oy).headerbytes > bytes as libc::c_int {
        return 0;
    }
    {
        let mut chksum: [libc::c_char; 4] = [0; 4];
        let mut log: ogg_page = ogg_page {
            header: std::ptr::null_mut(),
            header_len: 0,
            body: std::ptr::null_mut(),
            body_len: 0,
        };
        libc::memcpy(
            chksum.as_mut_ptr() as *mut libc::c_void,
            page.offset(22) as *const libc::c_void,
            4,
        );
        libc::memset(page.offset(22) as *mut libc::c_void, 0, 4);
        log.header = page;
        log.header_len = (*oy).headerbytes as libc::c_long;
        log.body = page.offset((*oy).headerbytes as isize);
        log.body_len = (*oy).bodybytes as libc::c_long;
        ogg_page_checksum_set(&mut log);
        if libc::memcmp(
            chksum.as_ptr() as *const libc::c_void,
            page.offset(22) as *const libc::c_void,
            4,
        ) != 0
        {
            libc::memcpy(
                page.offset(22) as *mut libc::c_void,
                chksum.as_ptr() as *const libc::c_void,
                4,
            );
            (*oy).headerbytes = 0;
            (*oy).bodybytes = 0;
            next = libc::memchr(
                page.offset(1) as *const libc::c_void,
                b'O' as libc::c_int,
                (bytes - 1) as libc::size_t,
            ) as *mut libc::c_uchar;
            if next.is_null() {
                next = (*oy).data.offset((*oy).fill as isize);
            }
            (*oy).returned = next.offset_from((*oy).data) as libc::c_int;
            return -(next.offset_from(page) as libc::c_long);
        }
    }
    {
        if !og.is_null() {
            (*og).header = page;
            (*og).header_len = (*oy).headerbytes as libc::c_long;
            (*og).body = page.offset((*oy).headerbytes as isize);
            (*og).body_len = (*oy).bodybytes as libc::c_long;
        }
        (*oy).unsynced = 0;
        (*oy).returned += (*oy).headerbytes + (*oy).bodybytes;
        bytes = (*oy).headerbytes as libc::c_long + (*oy).bodybytes as libc::c_long;
        (*oy).headerbytes = 0;
        (*oy).bodybytes = 0;
        return bytes;
    }
}
