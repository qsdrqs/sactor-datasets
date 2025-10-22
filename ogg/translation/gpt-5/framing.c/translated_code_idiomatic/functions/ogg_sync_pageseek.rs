pub fn ogg_sync_pageseek<'a>(
    oy: &'a mut OggSyncState<'a>,
    mut og: Option<&'a mut OggPage<'a>>,
) -> isize {
    fn seek_to_next_sync<'a>(oy: &mut OggSyncState<'a>, start: usize) -> isize {
        let search_start = start.saturating_add(1);
        let next_index = if search_start < oy.fill {
            let search_slice = &oy.data[search_start..oy.fill];
            if let Some(pos) = search_slice.iter().position(|&b| b == b'O') {
                search_start + pos
            } else {
                oy.fill
            }
        } else {
            oy.fill
        };
        oy.returned = next_index;
        -(next_index.saturating_sub(start) as isize)
    }
    if ogg_sync_check(&*oy) != 0 {
        return 0;
    }
    let start = oy.returned;
    if start >= oy.fill {
        return 0;
    }
    let bytes = oy.fill - start;
    if oy.headerbytes == 0 {
        if bytes < 27 {
            return 0;
        }
        if &oy.data[start..start + 4] != b"OggS" {
            oy.headerbytes = 0;
            oy.bodybytes = 0;
            return seek_to_next_sync(oy, start);
        }
        let page_segments = oy.data[start + 26] as usize;
        let headerbytes = 27 + page_segments;
        if bytes < headerbytes {
            return 0;
        }
        let lacing_start = start + 27;
        let lacing_end = lacing_start + page_segments;
        let bodybytes = oy.data[lacing_start..lacing_end]
            .iter()
            .fold(0usize, |acc, &v| acc + v as usize);
        oy.headerbytes = headerbytes;
        oy.bodybytes = bodybytes;
    }
    let total = oy.headerbytes + oy.bodybytes;
    if total > bytes {
        return 0;
    }
    let checksum_ok = {
        let page_slice = &mut oy.data[start..start + total];
        let mut chksum = [0u8; 4];
        chksum.copy_from_slice(&page_slice[22..26]);
        page_slice[22..26].fill(0);
        {
            let (header_part, rest) = page_slice.split_at_mut(oy.headerbytes);
            let body_part: &[u8] = &rest[..oy.bodybytes];
            let mut temp_page = OggPage {
                header: header_part,
                body: body_part,
            };
            ogg_page_checksum_set(&mut temp_page);
        }
        let ok = &page_slice[22..26] == &chksum;
        if !ok {
            page_slice[22..26].copy_from_slice(&chksum);
        }
        ok
    };
    if !checksum_ok {
        oy.headerbytes = 0;
        oy.bodybytes = 0;
        return seek_to_next_sync(oy, start);
    }
    if let Some(ref mut out_og) = og {
        let (_, after_start) = oy.data.split_at_mut(start);
        let (header_mut, rest) = after_start.split_at_mut(oy.headerbytes);
        let body_slice: &[u8] = &rest[..oy.bodybytes];
        out_og.header = header_mut;
        out_og.body = body_slice;
    }
    oy.unsynced = false;
    oy.returned = oy.returned.saturating_add(total);
    oy.headerbytes = 0;
    oy.bodybytes = 0;
    total as isize
}
