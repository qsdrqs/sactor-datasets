pub unsafe fn ogg_sync_pageseek(oy: *mut ogg_sync_state, og: *mut ogg_page) -> libc::c_long {
    let mut page: *mut libc::c_uchar;
    let mut bytes: libc::c_long;
    if ogg_sync_check(oy) != 0 {
        return 0;
    }
    page = (*oy).data.add((*oy).returned as usize);
    bytes = ((*oy).fill - (*oy).returned) as libc::c_long;
    if (*oy).headerbytes == 0 {
        let mut headerbytes: libc::c_int;
        let mut i: libc::c_int;
        if bytes < 27 {
            return 0;
        }
        if libc::memcmp(
            page as *const libc::c_void,
            b"OggS".as_ptr() as *const libc::c_void,
            4,
        ) != 0
        {
            (*oy).headerbytes = 0;
            (*oy).bodybytes = 0;
            let n = if bytes > 1 {
                (bytes - 1) as usize
            } else {
                0usize
            };
            let mut next = libc::memchr(page.add(1) as *const libc::c_void, 'O' as libc::c_int, n)
                as *mut libc::c_uchar;
            if next.is_null() {
                next = (*oy).data.add((*oy).fill as usize);
            }
            (*oy).returned = next.offset_from((*oy).data) as libc::c_int;
            return -(next.offset_from(page) as libc::c_long);
        }
        headerbytes = *page.add(26) as libc::c_int + 27;
        if bytes < headerbytes as libc::c_long {
            return 0;
        }
        i = 0;
        while i < *page.add(26) as libc::c_int {
            (*oy).bodybytes += *page.add(27 + i as usize) as libc::c_int;
            i += 1;
        }
        (*oy).headerbytes = headerbytes;
    }
    if ((*oy).bodybytes + (*oy).headerbytes) as libc::c_long > bytes {
        return 0;
    }
    {
        let mut chksum: [libc::c_uchar; 4] = [0; 4];
        let mut log = ogg_page {
            header: core::ptr::null_mut(),
            header_len: 0,
            body: core::ptr::null_mut(),
            body_len: 0,
        };
        libc::memcpy(
            chksum.as_mut_ptr() as *mut libc::c_void,
            page.add(22) as *const libc::c_void,
            4,
        );
        libc::memset(page.add(22) as *mut libc::c_void, 0, 4);
        log.header = page;
        log.header_len = (*oy).headerbytes as libc::c_long;
        log.body = page.add((*oy).headerbytes as usize);
        log.body_len = (*oy).bodybytes as libc::c_long;
        ogg_page_checksum_set(&mut log as *mut ogg_page);
        if libc::memcmp(
            chksum.as_ptr() as *const libc::c_void,
            page.add(22) as *const libc::c_void,
            4,
        ) != 0
        {
            libc::memcpy(
                page.add(22) as *mut libc::c_void,
                chksum.as_ptr() as *const libc::c_void,
                4,
            );
            (*oy).headerbytes = 0;
            (*oy).bodybytes = 0;
            let n = if bytes > 1 {
                (bytes - 1) as usize
            } else {
                0usize
            };
            let mut next = libc::memchr(page.add(1) as *const libc::c_void, 'O' as libc::c_int, n)
                as *mut libc::c_uchar;
            if next.is_null() {
                next = (*oy).data.add((*oy).fill as usize);
            }
            (*oy).returned = next.offset_from((*oy).data) as libc::c_int;
            return -(next.offset_from(page) as libc::c_long);
        }
    }
    {
        if !og.is_null() {
            (*og).header = page;
            (*og).header_len = (*oy).headerbytes as libc::c_long;
            (*og).body = page.add((*oy).headerbytes as usize);
            (*og).body_len = (*oy).bodybytes as libc::c_long;
        }
        (*oy).unsynced = 0;
        bytes = ((*oy).headerbytes + (*oy).bodybytes) as libc::c_long;
        (*oy).returned += bytes as libc::c_int;
        (*oy).headerbytes = 0;
        (*oy).bodybytes = 0;
        return bytes;
    }
}
