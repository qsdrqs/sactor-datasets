pub unsafe fn ogg_sync_buffer(oy: *mut ogg_sync_state, size: libc::c_long) -> *mut libc::c_char {
    if ogg_sync_check(oy) != 0 {
        return core::ptr::null_mut();
    }
    let oy = &mut *oy;
    if oy.returned != 0 {
        oy.fill -= oy.returned;
        if oy.fill > 0 {
            libc::memmove(
                oy.data as *mut libc::c_void,
                oy.data.add(oy.returned as usize) as *const libc::c_void,
                oy.fill as usize,
            );
        }
        oy.returned = 0;
    }
    let available: libc::c_long = (oy.storage - oy.fill) as libc::c_long;
    if size > available {
        let limit: i64 = (i32::MAX as i64) - 4096 - (oy.fill as i64);
        if (size as i64) > limit {
            ogg_sync_clear(oy as *mut ogg_sync_state);
            return core::ptr::null_mut();
        }
        let newsize: libc::c_long = size + oy.fill as libc::c_long + 4096 as libc::c_long;
        let ret = if !oy.data.is_null() {
            libc::realloc(oy.data as *mut libc::c_void, newsize as usize)
        } else {
            libc::malloc(newsize as usize)
        };
        if ret.is_null() {
            ogg_sync_clear(oy as *mut ogg_sync_state);
            return core::ptr::null_mut();
        }
        oy.data = ret as *mut libc::c_uchar;
        oy.storage = newsize as libc::c_int;
    }
    (oy.data as *mut libc::c_char).add(oy.fill as usize)
}
