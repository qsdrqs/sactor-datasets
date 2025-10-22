use libc::c_char;
use libc::c_int;
use libc::c_long;
use libc::c_uchar;
use libc::c_void;
use libc::free;
use libc::malloc;
use libc::memcpy;
use libc::memmove;
use libc::memset;
use libc::realloc;
use libc::size_t;
use libc::INT_MAX;
use std::i64;
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_page {
    pub header: *mut libc::c_uchar,
    pub header_len: libc::c_long,
    pub body: *mut libc::c_uchar,
    pub body_len: libc::c_long,
}
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_stream_state {
    pub body_data: *mut libc::c_uchar,
    pub body_storage: libc::c_long,
    pub body_fill: libc::c_long,
    pub body_returned: libc::c_long,
    pub lacing_vals: *mut libc::c_int,
    pub granule_vals: *mut libc::c_long,
    pub lacing_storage: libc::c_long,
    pub lacing_fill: libc::c_long,
    pub lacing_packet: libc::c_long,
    pub lacing_returned: libc::c_long,
    pub header: [libc::c_uchar; 282],
    pub header_fill: libc::c_int,
    pub e_o_s: libc::c_int,
    pub b_o_s: libc::c_int,
    pub serialno: libc::c_long,
    pub pageno: libc::c_long,
    pub packetno: libc::c_long,
    pub granulepos: libc::c_long,
}
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_iovec_t {
    pub iov_base: *mut libc::c_void,
    pub iov_len: size_t,
}
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_packet {
    pub packet: *mut libc::c_uchar,
    pub bytes: libc::c_long,
    pub b_o_s: libc::c_long,
    pub e_o_s: libc::c_long,
    pub granulepos: libc::c_long,
    pub packetno: libc::c_long,
}
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct ogg_sync_state {
    pub data: *mut libc::c_uchar,
    pub storage: libc::c_int,
    pub fill: libc::c_int,
    pub returned: libc::c_int,
    pub unsynced: libc::c_int,
    pub headerbytes: libc::c_int,
    pub bodybytes: libc::c_int,
}
static crc_lookup: [[libc::c_uint; 256]; 8] = [
    [
        0 as libc::c_int as libc::c_uint,
        0x4c11db7 as libc::c_int as libc::c_uint,
        0x9823b6e as libc::c_int as libc::c_uint,
        0xd4326d9 as libc::c_int as libc::c_uint,
        0x130476dc as libc::c_int as libc::c_uint,
        0x17c56b6b as libc::c_int as libc::c_uint,
        0x1a864db2 as libc::c_int as libc::c_uint,
        0x1e475005 as libc::c_int as libc::c_uint,
        0x2608edb8 as libc::c_int as libc::c_uint,
        0x22c9f00f as libc::c_int as libc::c_uint,
        0x2f8ad6d6 as libc::c_int as libc::c_uint,
        0x2b4bcb61 as libc::c_int as libc::c_uint,
        0x350c9b64 as libc::c_int as libc::c_uint,
        0x31cd86d3 as libc::c_int as libc::c_uint,
        0x3c8ea00a as libc::c_int as libc::c_uint,
        0x384fbdbd as libc::c_int as libc::c_uint,
        0x4c11db70 as libc::c_int as libc::c_uint,
        0x48d0c6c7 as libc::c_int as libc::c_uint,
        0x4593e01e as libc::c_int as libc::c_uint,
        0x4152fda9 as libc::c_int as libc::c_uint,
        0x5f15adac as libc::c_int as libc::c_uint,
        0x5bd4b01b as libc::c_int as libc::c_uint,
        0x569796c2 as libc::c_int as libc::c_uint,
        0x52568b75 as libc::c_int as libc::c_uint,
        0x6a1936c8 as libc::c_int as libc::c_uint,
        0x6ed82b7f as libc::c_int as libc::c_uint,
        0x639b0da6 as libc::c_int as libc::c_uint,
        0x675a1011 as libc::c_int as libc::c_uint,
        0x791d4014 as libc::c_int as libc::c_uint,
        0x7ddc5da3 as libc::c_int as libc::c_uint,
        0x709f7b7a as libc::c_int as libc::c_uint,
        0x745e66cd as libc::c_int as libc::c_uint,
        0x9823b6e0 as libc::c_uint,
        0x9ce2ab57 as libc::c_uint,
        0x91a18d8e as libc::c_uint,
        0x95609039 as libc::c_uint,
        0x8b27c03c as libc::c_uint,
        0x8fe6dd8b as libc::c_uint,
        0x82a5fb52 as libc::c_uint,
        0x8664e6e5 as libc::c_uint,
        0xbe2b5b58 as libc::c_uint,
        0xbaea46ef as libc::c_uint,
        0xb7a96036 as libc::c_uint,
        0xb3687d81 as libc::c_uint,
        0xad2f2d84 as libc::c_uint,
        0xa9ee3033 as libc::c_uint,
        0xa4ad16ea as libc::c_uint,
        0xa06c0b5d as libc::c_uint,
        0xd4326d90 as libc::c_uint,
        0xd0f37027 as libc::c_uint,
        0xddb056fe as libc::c_uint,
        0xd9714b49 as libc::c_uint,
        0xc7361b4c as libc::c_uint,
        0xc3f706fb as libc::c_uint,
        0xceb42022 as libc::c_uint,
        0xca753d95 as libc::c_uint,
        0xf23a8028 as libc::c_uint,
        0xf6fb9d9f as libc::c_uint,
        0xfbb8bb46 as libc::c_uint,
        0xff79a6f1 as libc::c_uint,
        0xe13ef6f4 as libc::c_uint,
        0xe5ffeb43 as libc::c_uint,
        0xe8bccd9a as libc::c_uint,
        0xec7dd02d as libc::c_uint,
        0x34867077 as libc::c_int as libc::c_uint,
        0x30476dc0 as libc::c_int as libc::c_uint,
        0x3d044b19 as libc::c_int as libc::c_uint,
        0x39c556ae as libc::c_int as libc::c_uint,
        0x278206ab as libc::c_int as libc::c_uint,
        0x23431b1c as libc::c_int as libc::c_uint,
        0x2e003dc5 as libc::c_int as libc::c_uint,
        0x2ac12072 as libc::c_int as libc::c_uint,
        0x128e9dcf as libc::c_int as libc::c_uint,
        0x164f8078 as libc::c_int as libc::c_uint,
        0x1b0ca6a1 as libc::c_int as libc::c_uint,
        0x1fcdbb16 as libc::c_int as libc::c_uint,
        0x18aeb13 as libc::c_int as libc::c_uint,
        0x54bf6a4 as libc::c_int as libc::c_uint,
        0x808d07d as libc::c_int as libc::c_uint,
        0xcc9cdca as libc::c_int as libc::c_uint,
        0x7897ab07 as libc::c_int as libc::c_uint,
        0x7c56b6b0 as libc::c_int as libc::c_uint,
        0x71159069 as libc::c_int as libc::c_uint,
        0x75d48dde as libc::c_int as libc::c_uint,
        0x6b93dddb as libc::c_int as libc::c_uint,
        0x6f52c06c as libc::c_int as libc::c_uint,
        0x6211e6b5 as libc::c_int as libc::c_uint,
        0x66d0fb02 as libc::c_int as libc::c_uint,
        0x5e9f46bf as libc::c_int as libc::c_uint,
        0x5a5e5b08 as libc::c_int as libc::c_uint,
        0x571d7dd1 as libc::c_int as libc::c_uint,
        0x53dc6066 as libc::c_int as libc::c_uint,
        0x4d9b3063 as libc::c_int as libc::c_uint,
        0x495a2dd4 as libc::c_int as libc::c_uint,
        0x44190b0d as libc::c_int as libc::c_uint,
        0x40d816ba as libc::c_int as libc::c_uint,
        0xaca5c697 as libc::c_uint,
        0xa864db20 as libc::c_uint,
        0xa527fdf9 as libc::c_uint,
        0xa1e6e04e as libc::c_uint,
        0xbfa1b04b as libc::c_uint,
        0xbb60adfc as libc::c_uint,
        0xb6238b25 as libc::c_uint,
        0xb2e29692 as libc::c_uint,
        0x8aad2b2f as libc::c_uint,
        0x8e6c3698 as libc::c_uint,
        0x832f1041 as libc::c_uint,
        0x87ee0df6 as libc::c_uint,
        0x99a95df3 as libc::c_uint,
        0x9d684044 as libc::c_uint,
        0x902b669d as libc::c_uint,
        0x94ea7b2a as libc::c_uint,
        0xe0b41de7 as libc::c_uint,
        0xe4750050 as libc::c_uint,
        0xe9362689 as libc::c_uint,
        0xedf73b3e as libc::c_uint,
        0xf3b06b3b as libc::c_uint,
        0xf771768c as libc::c_uint,
        0xfa325055 as libc::c_uint,
        0xfef34de2 as libc::c_uint,
        0xc6bcf05f as libc::c_uint,
        0xc27dede8 as libc::c_uint,
        0xcf3ecb31 as libc::c_uint,
        0xcbffd686 as libc::c_uint,
        0xd5b88683 as libc::c_uint,
        0xd1799b34 as libc::c_uint,
        0xdc3abded as libc::c_uint,
        0xd8fba05a as libc::c_uint,
        0x690ce0ee as libc::c_int as libc::c_uint,
        0x6dcdfd59 as libc::c_int as libc::c_uint,
        0x608edb80 as libc::c_int as libc::c_uint,
        0x644fc637 as libc::c_int as libc::c_uint,
        0x7a089632 as libc::c_int as libc::c_uint,
        0x7ec98b85 as libc::c_int as libc::c_uint,
        0x738aad5c as libc::c_int as libc::c_uint,
        0x774bb0eb as libc::c_int as libc::c_uint,
        0x4f040d56 as libc::c_int as libc::c_uint,
        0x4bc510e1 as libc::c_int as libc::c_uint,
        0x46863638 as libc::c_int as libc::c_uint,
        0x42472b8f as libc::c_int as libc::c_uint,
        0x5c007b8a as libc::c_int as libc::c_uint,
        0x58c1663d as libc::c_int as libc::c_uint,
        0x558240e4 as libc::c_int as libc::c_uint,
        0x51435d53 as libc::c_int as libc::c_uint,
        0x251d3b9e as libc::c_int as libc::c_uint,
        0x21dc2629 as libc::c_int as libc::c_uint,
        0x2c9f00f0 as libc::c_int as libc::c_uint,
        0x285e1d47 as libc::c_int as libc::c_uint,
        0x36194d42 as libc::c_int as libc::c_uint,
        0x32d850f5 as libc::c_int as libc::c_uint,
        0x3f9b762c as libc::c_int as libc::c_uint,
        0x3b5a6b9b as libc::c_int as libc::c_uint,
        0x315d626 as libc::c_int as libc::c_uint,
        0x7d4cb91 as libc::c_int as libc::c_uint,
        0xa97ed48 as libc::c_int as libc::c_uint,
        0xe56f0ff as libc::c_int as libc::c_uint,
        0x1011a0fa as libc::c_int as libc::c_uint,
        0x14d0bd4d as libc::c_int as libc::c_uint,
        0x19939b94 as libc::c_int as libc::c_uint,
        0x1d528623 as libc::c_int as libc::c_uint,
        0xf12f560e as libc::c_uint,
        0xf5ee4bb9 as libc::c_uint,
        0xf8ad6d60 as libc::c_uint,
        0xfc6c70d7 as libc::c_uint,
        0xe22b20d2 as libc::c_uint,
        0xe6ea3d65 as libc::c_uint,
        0xeba91bbc as libc::c_uint,
        0xef68060b as libc::c_uint,
        0xd727bbb6 as libc::c_uint,
        0xd3e6a601 as libc::c_uint,
        0xdea580d8 as libc::c_uint,
        0xda649d6f as libc::c_uint,
        0xc423cd6a as libc::c_uint,
        0xc0e2d0dd as libc::c_uint,
        0xcda1f604 as libc::c_uint,
        0xc960ebb3 as libc::c_uint,
        0xbd3e8d7e as libc::c_uint,
        0xb9ff90c9 as libc::c_uint,
        0xb4bcb610 as libc::c_uint,
        0xb07daba7 as libc::c_uint,
        0xae3afba2 as libc::c_uint,
        0xaafbe615 as libc::c_uint,
        0xa7b8c0cc as libc::c_uint,
        0xa379dd7b as libc::c_uint,
        0x9b3660c6 as libc::c_uint,
        0x9ff77d71 as libc::c_uint,
        0x92b45ba8 as libc::c_uint,
        0x9675461f as libc::c_uint,
        0x8832161a as libc::c_uint,
        0x8cf30bad as libc::c_uint,
        0x81b02d74 as libc::c_uint,
        0x857130c3 as libc::c_uint,
        0x5d8a9099 as libc::c_int as libc::c_uint,
        0x594b8d2e as libc::c_int as libc::c_uint,
        0x5408abf7 as libc::c_int as libc::c_uint,
        0x50c9b640 as libc::c_int as libc::c_uint,
        0x4e8ee645 as libc::c_int as libc::c_uint,
        0x4a4ffbf2 as libc::c_int as libc::c_uint,
        0x470cdd2b as libc::c_int as libc::c_uint,
        0x43cdc09c as libc::c_int as libc::c_uint,
        0x7b827d21 as libc::c_int as libc::c_uint,
        0x7f436096 as libc::c_int as libc::c_uint,
        0x7200464f as libc::c_int as libc::c_uint,
        0x76c15bf8 as libc::c_int as libc::c_uint,
        0x68860bfd as libc::c_int as libc::c_uint,
        0x6c47164a as libc::c_int as libc::c_uint,
        0x61043093 as libc::c_int as libc::c_uint,
        0x65c52d24 as libc::c_int as libc::c_uint,
        0x119b4be9 as libc::c_int as libc::c_uint,
        0x155a565e as libc::c_int as libc::c_uint,
        0x18197087 as libc::c_int as libc::c_uint,
        0x1cd86d30 as libc::c_int as libc::c_uint,
        0x29f3d35 as libc::c_int as libc::c_uint,
        0x65e2082 as libc::c_int as libc::c_uint,
        0xb1d065b as libc::c_int as libc::c_uint,
        0xfdc1bec as libc::c_int as libc::c_uint,
        0x3793a651 as libc::c_int as libc::c_uint,
        0x3352bbe6 as libc::c_int as libc::c_uint,
        0x3e119d3f as libc::c_int as libc::c_uint,
        0x3ad08088 as libc::c_int as libc::c_uint,
        0x2497d08d as libc::c_int as libc::c_uint,
        0x2056cd3a as libc::c_int as libc::c_uint,
        0x2d15ebe3 as libc::c_int as libc::c_uint,
        0x29d4f654 as libc::c_int as libc::c_uint,
        0xc5a92679 as libc::c_uint,
        0xc1683bce as libc::c_uint,
        0xcc2b1d17 as libc::c_uint,
        0xc8ea00a0 as libc::c_uint,
        0xd6ad50a5 as libc::c_uint,
        0xd26c4d12 as libc::c_uint,
        0xdf2f6bcb as libc::c_uint,
        0xdbee767c as libc::c_uint,
        0xe3a1cbc1 as libc::c_uint,
        0xe760d676 as libc::c_uint,
        0xea23f0af as libc::c_uint,
        0xeee2ed18 as libc::c_uint,
        0xf0a5bd1d as libc::c_uint,
        0xf464a0aa as libc::c_uint,
        0xf9278673 as libc::c_uint,
        0xfde69bc4 as libc::c_uint,
        0x89b8fd09 as libc::c_uint,
        0x8d79e0be as libc::c_uint,
        0x803ac667 as libc::c_uint,
        0x84fbdbd0 as libc::c_uint,
        0x9abc8bd5 as libc::c_uint,
        0x9e7d9662 as libc::c_uint,
        0x933eb0bb as libc::c_uint,
        0x97ffad0c as libc::c_uint,
        0xafb010b1 as libc::c_uint,
        0xab710d06 as libc::c_uint,
        0xa6322bdf as libc::c_uint,
        0xa2f33668 as libc::c_uint,
        0xbcb4666d as libc::c_uint,
        0xb8757bda as libc::c_uint,
        0xb5365d03 as libc::c_uint,
        0xb1f740b4 as libc::c_uint,
    ],
    [
        0 as libc::c_int as libc::c_uint,
        0xd219c1dc as libc::c_uint,
        0xa0f29e0f as libc::c_uint,
        0x72eb5fd3 as libc::c_int as libc::c_uint,
        0x452421a9 as libc::c_int as libc::c_uint,
        0x973de075 as libc::c_uint,
        0xe5d6bfa6 as libc::c_uint,
        0x37cf7e7a as libc::c_int as libc::c_uint,
        0x8a484352 as libc::c_uint,
        0x5851828e as libc::c_int as libc::c_uint,
        0x2abadd5d as libc::c_int as libc::c_uint,
        0xf8a31c81 as libc::c_uint,
        0xcf6c62fb as libc::c_uint,
        0x1d75a327 as libc::c_int as libc::c_uint,
        0x6f9efcf4 as libc::c_int as libc::c_uint,
        0xbd873d28 as libc::c_uint,
        0x10519b13 as libc::c_int as libc::c_uint,
        0xc2485acf as libc::c_uint,
        0xb0a3051c as libc::c_uint,
        0x62bac4c0 as libc::c_int as libc::c_uint,
        0x5575baba as libc::c_int as libc::c_uint,
        0x876c7b66 as libc::c_uint,
        0xf58724b5 as libc::c_uint,
        0x279ee569 as libc::c_int as libc::c_uint,
        0x9a19d841 as libc::c_uint,
        0x4800199d as libc::c_int as libc::c_uint,
        0x3aeb464e as libc::c_int as libc::c_uint,
        0xe8f28792 as libc::c_uint,
        0xdf3df9e8 as libc::c_uint,
        0xd243834 as libc::c_int as libc::c_uint,
        0x7fcf67e7 as libc::c_int as libc::c_uint,
        0xadd6a63b as libc::c_uint,
        0x20a33626 as libc::c_int as libc::c_uint,
        0xf2baf7fa as libc::c_uint,
        0x8051a829 as libc::c_uint,
        0x524869f5 as libc::c_int as libc::c_uint,
        0x6587178f as libc::c_int as libc::c_uint,
        0xb79ed653 as libc::c_uint,
        0xc5758980 as libc::c_uint,
        0x176c485c as libc::c_int as libc::c_uint,
        0xaaeb7574 as libc::c_uint,
        0x78f2b4a8 as libc::c_int as libc::c_uint,
        0xa19eb7b as libc::c_int as libc::c_uint,
        0xd8002aa7 as libc::c_uint,
        0xefcf54dd as libc::c_uint,
        0x3dd69501 as libc::c_int as libc::c_uint,
        0x4f3dcad2 as libc::c_int as libc::c_uint,
        0x9d240b0e as libc::c_uint,
        0x30f2ad35 as libc::c_int as libc::c_uint,
        0xe2eb6ce9 as libc::c_uint,
        0x9000333a as libc::c_uint,
        0x4219f2e6 as libc::c_int as libc::c_uint,
        0x75d68c9c as libc::c_int as libc::c_uint,
        0xa7cf4d40 as libc::c_uint,
        0xd5241293 as libc::c_uint,
        0x73dd34f as libc::c_int as libc::c_uint,
        0xbabaee67 as libc::c_uint,
        0x68a32fbb as libc::c_int as libc::c_uint,
        0x1a487068 as libc::c_int as libc::c_uint,
        0xc851b1b4 as libc::c_uint,
        0xff9ecfce as libc::c_uint,
        0x2d870e12 as libc::c_int as libc::c_uint,
        0x5f6c51c1 as libc::c_int as libc::c_uint,
        0x8d75901d as libc::c_uint,
        0x41466c4c as libc::c_int as libc::c_uint,
        0x935fad90 as libc::c_uint,
        0xe1b4f243 as libc::c_uint,
        0x33ad339f as libc::c_int as libc::c_uint,
        0x4624de5 as libc::c_int as libc::c_uint,
        0xd67b8c39 as libc::c_uint,
        0xa490d3ea as libc::c_uint,
        0x76891236 as libc::c_int as libc::c_uint,
        0xcb0e2f1e as libc::c_uint,
        0x1917eec2 as libc::c_int as libc::c_uint,
        0x6bfcb111 as libc::c_int as libc::c_uint,
        0xb9e570cd as libc::c_uint,
        0x8e2a0eb7 as libc::c_uint,
        0x5c33cf6b as libc::c_int as libc::c_uint,
        0x2ed890b8 as libc::c_int as libc::c_uint,
        0xfcc15164 as libc::c_uint,
        0x5117f75f as libc::c_int as libc::c_uint,
        0x830e3683 as libc::c_uint,
        0xf1e56950 as libc::c_uint,
        0x23fca88c as libc::c_int as libc::c_uint,
        0x1433d6f6 as libc::c_int as libc::c_uint,
        0xc62a172a as libc::c_uint,
        0xb4c148f9 as libc::c_uint,
        0x66d88925 as libc::c_int as libc::c_uint,
        0xdb5fb40d as libc::c_uint,
        0x94675d1 as libc::c_int as libc::c_uint,
        0x7bad2a02 as libc::c_int as libc::c_uint,
        0xa9b4ebde as libc::c_uint,
        0x9e7b95a4 as libc::c_uint,
        0x4c625478 as libc::c_int as libc::c_uint,
        0x3e890bab as libc::c_int as libc::c_uint,
        0xec90ca77 as libc::c_uint,
        0x61e55a6a as libc::c_int as libc::c_uint,
        0xb3fc9bb6 as libc::c_uint,
        0xc117c465 as libc::c_uint,
        0x130e05b9 as libc::c_int as libc::c_uint,
        0x24c17bc3 as libc::c_int as libc::c_uint,
        0xf6d8ba1f as libc::c_uint,
        0x8433e5cc as libc::c_uint,
        0x562a2410 as libc::c_int as libc::c_uint,
        0xebad1938 as libc::c_uint,
        0x39b4d8e4 as libc::c_int as libc::c_uint,
        0x4b5f8737 as libc::c_int as libc::c_uint,
        0x994646eb as libc::c_uint,
        0xae893891 as libc::c_uint,
        0x7c90f94d as libc::c_int as libc::c_uint,
        0xe7ba69e as libc::c_int as libc::c_uint,
        0xdc626742 as libc::c_uint,
        0x71b4c179 as libc::c_int as libc::c_uint,
        0xa3ad00a5 as libc::c_uint,
        0xd1465f76 as libc::c_uint,
        0x35f9eaa as libc::c_int as libc::c_uint,
        0x3490e0d0 as libc::c_int as libc::c_uint,
        0xe689210c as libc::c_uint,
        0x94627edf as libc::c_uint,
        0x467bbf03 as libc::c_int as libc::c_uint,
        0xfbfc822b as libc::c_uint,
        0x29e543f7 as libc::c_int as libc::c_uint,
        0x5b0e1c24 as libc::c_int as libc::c_uint,
        0x8917ddf8 as libc::c_uint,
        0xbed8a382 as libc::c_uint,
        0x6cc1625e as libc::c_int as libc::c_uint,
        0x1e2a3d8d as libc::c_int as libc::c_uint,
        0xcc33fc51 as libc::c_uint,
        0x828cd898 as libc::c_uint,
        0x50951944 as libc::c_int as libc::c_uint,
        0x227e4697 as libc::c_int as libc::c_uint,
        0xf067874b as libc::c_uint,
        0xc7a8f931 as libc::c_uint,
        0x15b138ed as libc::c_int as libc::c_uint,
        0x675a673e as libc::c_int as libc::c_uint,
        0xb543a6e2 as libc::c_uint,
        0x8c49bca as libc::c_int as libc::c_uint,
        0xdadd5a16 as libc::c_uint,
        0xa83605c5 as libc::c_uint,
        0x7a2fc419 as libc::c_int as libc::c_uint,
        0x4de0ba63 as libc::c_int as libc::c_uint,
        0x9ff97bbf as libc::c_uint,
        0xed12246c as libc::c_uint,
        0x3f0be5b0 as libc::c_int as libc::c_uint,
        0x92dd438b as libc::c_uint,
        0x40c48257 as libc::c_int as libc::c_uint,
        0x322fdd84 as libc::c_int as libc::c_uint,
        0xe0361c58 as libc::c_uint,
        0xd7f96222 as libc::c_uint,
        0x5e0a3fe as libc::c_int as libc::c_uint,
        0x770bfc2d as libc::c_int as libc::c_uint,
        0xa5123df1 as libc::c_uint,
        0x189500d9 as libc::c_int as libc::c_uint,
        0xca8cc105 as libc::c_uint,
        0xb8679ed6 as libc::c_uint,
        0x6a7e5f0a as libc::c_int as libc::c_uint,
        0x5db12170 as libc::c_int as libc::c_uint,
        0x8fa8e0ac as libc::c_uint,
        0xfd43bf7f as libc::c_uint,
        0x2f5a7ea3 as libc::c_int as libc::c_uint,
        0xa22feebe as libc::c_uint,
        0x70362f62 as libc::c_int as libc::c_uint,
        0x2dd70b1 as libc::c_int as libc::c_uint,
        0xd0c4b16d as libc::c_uint,
        0xe70bcf17 as libc::c_uint,
        0x35120ecb as libc::c_int as libc::c_uint,
        0x47f95118 as libc::c_int as libc::c_uint,
        0x95e090c4 as libc::c_uint,
        0x2867adec as libc::c_int as libc::c_uint,
        0xfa7e6c30 as libc::c_uint,
        0x889533e3 as libc::c_uint,
        0x5a8cf23f as libc::c_int as libc::c_uint,
        0x6d438c45 as libc::c_int as libc::c_uint,
        0xbf5a4d99 as libc::c_uint,
        0xcdb1124a as libc::c_uint,
        0x1fa8d396 as libc::c_int as libc::c_uint,
        0xb27e75ad as libc::c_uint,
        0x6067b471 as libc::c_int as libc::c_uint,
        0x128ceba2 as libc::c_int as libc::c_uint,
        0xc0952a7e as libc::c_uint,
        0xf75a5404 as libc::c_uint,
        0x254395d8 as libc::c_int as libc::c_uint,
        0x57a8ca0b as libc::c_int as libc::c_uint,
        0x85b10bd7 as libc::c_uint,
        0x383636ff as libc::c_int as libc::c_uint,
        0xea2ff723 as libc::c_uint,
        0x98c4a8f0 as libc::c_uint,
        0x4add692c as libc::c_int as libc::c_uint,
        0x7d121756 as libc::c_int as libc::c_uint,
        0xaf0bd68a as libc::c_uint,
        0xdde08959 as libc::c_uint,
        0xff94885 as libc::c_int as libc::c_uint,
        0xc3cab4d4 as libc::c_uint,
        0x11d37508 as libc::c_int as libc::c_uint,
        0x63382adb as libc::c_int as libc::c_uint,
        0xb121eb07 as libc::c_uint,
        0x86ee957d as libc::c_uint,
        0x54f754a1 as libc::c_int as libc::c_uint,
        0x261c0b72 as libc::c_int as libc::c_uint,
        0xf405caae as libc::c_uint,
        0x4982f786 as libc::c_int as libc::c_uint,
        0x9b9b365a as libc::c_uint,
        0xe9706989 as libc::c_uint,
        0x3b69a855 as libc::c_int as libc::c_uint,
        0xca6d62f as libc::c_int as libc::c_uint,
        0xdebf17f3 as libc::c_uint,
        0xac544820 as libc::c_uint,
        0x7e4d89fc as libc::c_int as libc::c_uint,
        0xd39b2fc7 as libc::c_uint,
        0x182ee1b as libc::c_int as libc::c_uint,
        0x7369b1c8 as libc::c_int as libc::c_uint,
        0xa1707014 as libc::c_uint,
        0x96bf0e6e as libc::c_uint,
        0x44a6cfb2 as libc::c_int as libc::c_uint,
        0x364d9061 as libc::c_int as libc::c_uint,
        0xe45451bd as libc::c_uint,
        0x59d36c95 as libc::c_int as libc::c_uint,
        0x8bcaad49 as libc::c_uint,
        0xf921f29a as libc::c_uint,
        0x2b383346 as libc::c_int as libc::c_uint,
        0x1cf74d3c as libc::c_int as libc::c_uint,
        0xceee8ce0 as libc::c_uint,
        0xbc05d333 as libc::c_uint,
        0x6e1c12ef as libc::c_int as libc::c_uint,
        0xe36982f2 as libc::c_uint,
        0x3170432e as libc::c_int as libc::c_uint,
        0x439b1cfd as libc::c_int as libc::c_uint,
        0x9182dd21 as libc::c_uint,
        0xa64da35b as libc::c_uint,
        0x74546287 as libc::c_int as libc::c_uint,
        0x6bf3d54 as libc::c_int as libc::c_uint,
        0xd4a6fc88 as libc::c_uint,
        0x6921c1a0 as libc::c_int as libc::c_uint,
        0xbb38007c as libc::c_uint,
        0xc9d35faf as libc::c_uint,
        0x1bca9e73 as libc::c_int as libc::c_uint,
        0x2c05e009 as libc::c_int as libc::c_uint,
        0xfe1c21d5 as libc::c_uint,
        0x8cf77e06 as libc::c_uint,
        0x5eeebfda as libc::c_int as libc::c_uint,
        0xf33819e1 as libc::c_uint,
        0x2121d83d as libc::c_int as libc::c_uint,
        0x53ca87ee as libc::c_int as libc::c_uint,
        0x81d34632 as libc::c_uint,
        0xb61c3848 as libc::c_uint,
        0x6405f994 as libc::c_int as libc::c_uint,
        0x16eea647 as libc::c_int as libc::c_uint,
        0xc4f7679b as libc::c_uint,
        0x79705ab3 as libc::c_int as libc::c_uint,
        0xab699b6f as libc::c_uint,
        0xd982c4bc as libc::c_uint,
        0xb9b0560 as libc::c_int as libc::c_uint,
        0x3c547b1a as libc::c_int as libc::c_uint,
        0xee4dbac6 as libc::c_uint,
        0x9ca6e515 as libc::c_uint,
        0x4ebf24c9 as libc::c_int as libc::c_uint,
    ],
    [
        0 as libc::c_int as libc::c_uint,
        0x1d8ac87 as libc::c_int as libc::c_uint,
        0x3b1590e as libc::c_int as libc::c_uint,
        0x269f589 as libc::c_int as libc::c_uint,
        0x762b21c as libc::c_int as libc::c_uint,
        0x6ba1e9b as libc::c_int as libc::c_uint,
        0x4d3eb12 as libc::c_int as libc::c_uint,
        0x50b4795 as libc::c_int as libc::c_uint,
        0xec56438 as libc::c_int as libc::c_uint,
        0xf1dc8bf as libc::c_int as libc::c_uint,
        0xd743d36 as libc::c_int as libc::c_uint,
        0xcac91b1 as libc::c_int as libc::c_uint,
        0x9a7d624 as libc::c_int as libc::c_uint,
        0x87f7aa3 as libc::c_int as libc::c_uint,
        0xa168f2a as libc::c_int as libc::c_uint,
        0xbce23ad as libc::c_int as libc::c_uint,
        0x1d8ac870 as libc::c_int as libc::c_uint,
        0x1c5264f7 as libc::c_int as libc::c_uint,
        0x1e3b917e as libc::c_int as libc::c_uint,
        0x1fe33df9 as libc::c_int as libc::c_uint,
        0x1ae87a6c as libc::c_int as libc::c_uint,
        0x1b30d6eb as libc::c_int as libc::c_uint,
        0x19592362 as libc::c_int as libc::c_uint,
        0x18818fe5 as libc::c_int as libc::c_uint,
        0x134fac48 as libc::c_int as libc::c_uint,
        0x129700cf as libc::c_int as libc::c_uint,
        0x10fef546 as libc::c_int as libc::c_uint,
        0x112659c1 as libc::c_int as libc::c_uint,
        0x142d1e54 as libc::c_int as libc::c_uint,
        0x15f5b2d3 as libc::c_int as libc::c_uint,
        0x179c475a as libc::c_int as libc::c_uint,
        0x1644ebdd as libc::c_int as libc::c_uint,
        0x3b1590e0 as libc::c_int as libc::c_uint,
        0x3acd3c67 as libc::c_int as libc::c_uint,
        0x38a4c9ee as libc::c_int as libc::c_uint,
        0x397c6569 as libc::c_int as libc::c_uint,
        0x3c7722fc as libc::c_int as libc::c_uint,
        0x3daf8e7b as libc::c_int as libc::c_uint,
        0x3fc67bf2 as libc::c_int as libc::c_uint,
        0x3e1ed775 as libc::c_int as libc::c_uint,
        0x35d0f4d8 as libc::c_int as libc::c_uint,
        0x3408585f as libc::c_int as libc::c_uint,
        0x3661add6 as libc::c_int as libc::c_uint,
        0x37b90151 as libc::c_int as libc::c_uint,
        0x32b246c4 as libc::c_int as libc::c_uint,
        0x336aea43 as libc::c_int as libc::c_uint,
        0x31031fca as libc::c_int as libc::c_uint,
        0x30dbb34d as libc::c_int as libc::c_uint,
        0x269f5890 as libc::c_int as libc::c_uint,
        0x2747f417 as libc::c_int as libc::c_uint,
        0x252e019e as libc::c_int as libc::c_uint,
        0x24f6ad19 as libc::c_int as libc::c_uint,
        0x21fdea8c as libc::c_int as libc::c_uint,
        0x2025460b as libc::c_int as libc::c_uint,
        0x224cb382 as libc::c_int as libc::c_uint,
        0x23941f05 as libc::c_int as libc::c_uint,
        0x285a3ca8 as libc::c_int as libc::c_uint,
        0x2982902f as libc::c_int as libc::c_uint,
        0x2beb65a6 as libc::c_int as libc::c_uint,
        0x2a33c921 as libc::c_int as libc::c_uint,
        0x2f388eb4 as libc::c_int as libc::c_uint,
        0x2ee02233 as libc::c_int as libc::c_uint,
        0x2c89d7ba as libc::c_int as libc::c_uint,
        0x2d517b3d as libc::c_int as libc::c_uint,
        0x762b21c0 as libc::c_int as libc::c_uint,
        0x77f38d47 as libc::c_int as libc::c_uint,
        0x759a78ce as libc::c_int as libc::c_uint,
        0x7442d449 as libc::c_int as libc::c_uint,
        0x714993dc as libc::c_int as libc::c_uint,
        0x70913f5b as libc::c_int as libc::c_uint,
        0x72f8cad2 as libc::c_int as libc::c_uint,
        0x73206655 as libc::c_int as libc::c_uint,
        0x78ee45f8 as libc::c_int as libc::c_uint,
        0x7936e97f as libc::c_int as libc::c_uint,
        0x7b5f1cf6 as libc::c_int as libc::c_uint,
        0x7a87b071 as libc::c_int as libc::c_uint,
        0x7f8cf7e4 as libc::c_int as libc::c_uint,
        0x7e545b63 as libc::c_int as libc::c_uint,
        0x7c3daeea as libc::c_int as libc::c_uint,
        0x7de5026d as libc::c_int as libc::c_uint,
        0x6ba1e9b0 as libc::c_int as libc::c_uint,
        0x6a794537 as libc::c_int as libc::c_uint,
        0x6810b0be as libc::c_int as libc::c_uint,
        0x69c81c39 as libc::c_int as libc::c_uint,
        0x6cc35bac as libc::c_int as libc::c_uint,
        0x6d1bf72b as libc::c_int as libc::c_uint,
        0x6f7202a2 as libc::c_int as libc::c_uint,
        0x6eaaae25 as libc::c_int as libc::c_uint,
        0x65648d88 as libc::c_int as libc::c_uint,
        0x64bc210f as libc::c_int as libc::c_uint,
        0x66d5d486 as libc::c_int as libc::c_uint,
        0x670d7801 as libc::c_int as libc::c_uint,
        0x62063f94 as libc::c_int as libc::c_uint,
        0x63de9313 as libc::c_int as libc::c_uint,
        0x61b7669a as libc::c_int as libc::c_uint,
        0x606fca1d as libc::c_int as libc::c_uint,
        0x4d3eb120 as libc::c_int as libc::c_uint,
        0x4ce61da7 as libc::c_int as libc::c_uint,
        0x4e8fe82e as libc::c_int as libc::c_uint,
        0x4f5744a9 as libc::c_int as libc::c_uint,
        0x4a5c033c as libc::c_int as libc::c_uint,
        0x4b84afbb as libc::c_int as libc::c_uint,
        0x49ed5a32 as libc::c_int as libc::c_uint,
        0x4835f6b5 as libc::c_int as libc::c_uint,
        0x43fbd518 as libc::c_int as libc::c_uint,
        0x4223799f as libc::c_int as libc::c_uint,
        0x404a8c16 as libc::c_int as libc::c_uint,
        0x41922091 as libc::c_int as libc::c_uint,
        0x44996704 as libc::c_int as libc::c_uint,
        0x4541cb83 as libc::c_int as libc::c_uint,
        0x47283e0a as libc::c_int as libc::c_uint,
        0x46f0928d as libc::c_int as libc::c_uint,
        0x50b47950 as libc::c_int as libc::c_uint,
        0x516cd5d7 as libc::c_int as libc::c_uint,
        0x5305205e as libc::c_int as libc::c_uint,
        0x52dd8cd9 as libc::c_int as libc::c_uint,
        0x57d6cb4c as libc::c_int as libc::c_uint,
        0x560e67cb as libc::c_int as libc::c_uint,
        0x54679242 as libc::c_int as libc::c_uint,
        0x55bf3ec5 as libc::c_int as libc::c_uint,
        0x5e711d68 as libc::c_int as libc::c_uint,
        0x5fa9b1ef as libc::c_int as libc::c_uint,
        0x5dc04466 as libc::c_int as libc::c_uint,
        0x5c18e8e1 as libc::c_int as libc::c_uint,
        0x5913af74 as libc::c_int as libc::c_uint,
        0x58cb03f3 as libc::c_int as libc::c_uint,
        0x5aa2f67a as libc::c_int as libc::c_uint,
        0x5b7a5afd as libc::c_int as libc::c_uint,
        0xec564380 as libc::c_uint,
        0xed8eef07 as libc::c_uint,
        0xefe71a8e as libc::c_uint,
        0xee3fb609 as libc::c_uint,
        0xeb34f19c as libc::c_uint,
        0xeaec5d1b as libc::c_uint,
        0xe885a892 as libc::c_uint,
        0xe95d0415 as libc::c_uint,
        0xe29327b8 as libc::c_uint,
        0xe34b8b3f as libc::c_uint,
        0xe1227eb6 as libc::c_uint,
        0xe0fad231 as libc::c_uint,
        0xe5f195a4 as libc::c_uint,
        0xe4293923 as libc::c_uint,
        0xe640ccaa as libc::c_uint,
        0xe798602d as libc::c_uint,
        0xf1dc8bf0 as libc::c_uint,
        0xf0042777 as libc::c_uint,
        0xf26dd2fe as libc::c_uint,
        0xf3b57e79 as libc::c_uint,
        0xf6be39ec as libc::c_uint,
        0xf766956b as libc::c_uint,
        0xf50f60e2 as libc::c_uint,
        0xf4d7cc65 as libc::c_uint,
        0xff19efc8 as libc::c_uint,
        0xfec1434f as libc::c_uint,
        0xfca8b6c6 as libc::c_uint,
        0xfd701a41 as libc::c_uint,
        0xf87b5dd4 as libc::c_uint,
        0xf9a3f153 as libc::c_uint,
        0xfbca04da as libc::c_uint,
        0xfa12a85d as libc::c_uint,
        0xd743d360 as libc::c_uint,
        0xd69b7fe7 as libc::c_uint,
        0xd4f28a6e as libc::c_uint,
        0xd52a26e9 as libc::c_uint,
        0xd021617c as libc::c_uint,
        0xd1f9cdfb as libc::c_uint,
        0xd3903872 as libc::c_uint,
        0xd24894f5 as libc::c_uint,
        0xd986b758 as libc::c_uint,
        0xd85e1bdf as libc::c_uint,
        0xda37ee56 as libc::c_uint,
        0xdbef42d1 as libc::c_uint,
        0xdee40544 as libc::c_uint,
        0xdf3ca9c3 as libc::c_uint,
        0xdd555c4a as libc::c_uint,
        0xdc8df0cd as libc::c_uint,
        0xcac91b10 as libc::c_uint,
        0xcb11b797 as libc::c_uint,
        0xc978421e as libc::c_uint,
        0xc8a0ee99 as libc::c_uint,
        0xcdaba90c as libc::c_uint,
        0xcc73058b as libc::c_uint,
        0xce1af002 as libc::c_uint,
        0xcfc25c85 as libc::c_uint,
        0xc40c7f28 as libc::c_uint,
        0xc5d4d3af as libc::c_uint,
        0xc7bd2626 as libc::c_uint,
        0xc6658aa1 as libc::c_uint,
        0xc36ecd34 as libc::c_uint,
        0xc2b661b3 as libc::c_uint,
        0xc0df943a as libc::c_uint,
        0xc10738bd as libc::c_uint,
        0x9a7d6240 as libc::c_uint,
        0x9ba5cec7 as libc::c_uint,
        0x99cc3b4e as libc::c_uint,
        0x981497c9 as libc::c_uint,
        0x9d1fd05c as libc::c_uint,
        0x9cc77cdb as libc::c_uint,
        0x9eae8952 as libc::c_uint,
        0x9f7625d5 as libc::c_uint,
        0x94b80678 as libc::c_uint,
        0x9560aaff as libc::c_uint,
        0x97095f76 as libc::c_uint,
        0x96d1f3f1 as libc::c_uint,
        0x93dab464 as libc::c_uint,
        0x920218e3 as libc::c_uint,
        0x906bed6a as libc::c_uint,
        0x91b341ed as libc::c_uint,
        0x87f7aa30 as libc::c_uint,
        0x862f06b7 as libc::c_uint,
        0x8446f33e as libc::c_uint,
        0x859e5fb9 as libc::c_uint,
        0x8095182c as libc::c_uint,
        0x814db4ab as libc::c_uint,
        0x83244122 as libc::c_uint,
        0x82fceda5 as libc::c_uint,
        0x8932ce08 as libc::c_uint,
        0x88ea628f as libc::c_uint,
        0x8a839706 as libc::c_uint,
        0x8b5b3b81 as libc::c_uint,
        0x8e507c14 as libc::c_uint,
        0x8f88d093 as libc::c_uint,
        0x8de1251a as libc::c_uint,
        0x8c39899d as libc::c_uint,
        0xa168f2a0 as libc::c_uint,
        0xa0b05e27 as libc::c_uint,
        0xa2d9abae as libc::c_uint,
        0xa3010729 as libc::c_uint,
        0xa60a40bc as libc::c_uint,
        0xa7d2ec3b as libc::c_uint,
        0xa5bb19b2 as libc::c_uint,
        0xa463b535 as libc::c_uint,
        0xafad9698 as libc::c_uint,
        0xae753a1f as libc::c_uint,
        0xac1ccf96 as libc::c_uint,
        0xadc46311 as libc::c_uint,
        0xa8cf2484 as libc::c_uint,
        0xa9178803 as libc::c_uint,
        0xab7e7d8a as libc::c_uint,
        0xaaa6d10d as libc::c_uint,
        0xbce23ad0 as libc::c_uint,
        0xbd3a9657 as libc::c_uint,
        0xbf5363de as libc::c_uint,
        0xbe8bcf59 as libc::c_uint,
        0xbb8088cc as libc::c_uint,
        0xba58244b as libc::c_uint,
        0xb831d1c2 as libc::c_uint,
        0xb9e97d45 as libc::c_uint,
        0xb2275ee8 as libc::c_uint,
        0xb3fff26f as libc::c_uint,
        0xb19607e6 as libc::c_uint,
        0xb04eab61 as libc::c_uint,
        0xb545ecf4 as libc::c_uint,
        0xb49d4073 as libc::c_uint,
        0xb6f4b5fa as libc::c_uint,
        0xb72c197d as libc::c_uint,
    ],
    [
        0 as libc::c_int as libc::c_uint,
        0xdc6d9ab7 as libc::c_uint,
        0xbc1a28d9 as libc::c_uint,
        0x6077b26e as libc::c_int as libc::c_uint,
        0x7cf54c05 as libc::c_int as libc::c_uint,
        0xa098d6b2 as libc::c_uint,
        0xc0ef64dc as libc::c_uint,
        0x1c82fe6b as libc::c_int as libc::c_uint,
        0xf9ea980a as libc::c_uint,
        0x258702bd as libc::c_int as libc::c_uint,
        0x45f0b0d3 as libc::c_int as libc::c_uint,
        0x999d2a64 as libc::c_uint,
        0x851fd40f as libc::c_uint,
        0x59724eb8 as libc::c_int as libc::c_uint,
        0x3905fcd6 as libc::c_int as libc::c_uint,
        0xe5686661 as libc::c_uint,
        0xf7142da3 as libc::c_uint,
        0x2b79b714 as libc::c_int as libc::c_uint,
        0x4b0e057a as libc::c_int as libc::c_uint,
        0x97639fcd as libc::c_uint,
        0x8be161a6 as libc::c_uint,
        0x578cfb11 as libc::c_int as libc::c_uint,
        0x37fb497f as libc::c_int as libc::c_uint,
        0xeb96d3c8 as libc::c_uint,
        0xefeb5a9 as libc::c_int as libc::c_uint,
        0xd2932f1e as libc::c_uint,
        0xb2e49d70 as libc::c_uint,
        0x6e8907c7 as libc::c_int as libc::c_uint,
        0x720bf9ac as libc::c_int as libc::c_uint,
        0xae66631b as libc::c_uint,
        0xce11d175 as libc::c_uint,
        0x127c4bc2 as libc::c_int as libc::c_uint,
        0xeae946f1 as libc::c_uint,
        0x3684dc46 as libc::c_int as libc::c_uint,
        0x56f36e28 as libc::c_int as libc::c_uint,
        0x8a9ef49f as libc::c_uint,
        0x961c0af4 as libc::c_uint,
        0x4a719043 as libc::c_int as libc::c_uint,
        0x2a06222d as libc::c_int as libc::c_uint,
        0xf66bb89a as libc::c_uint,
        0x1303defb as libc::c_int as libc::c_uint,
        0xcf6e444c as libc::c_uint,
        0xaf19f622 as libc::c_uint,
        0x73746c95 as libc::c_int as libc::c_uint,
        0x6ff692fe as libc::c_int as libc::c_uint,
        0xb39b0849 as libc::c_uint,
        0xd3ecba27 as libc::c_uint,
        0xf812090 as libc::c_int as libc::c_uint,
        0x1dfd6b52 as libc::c_int as libc::c_uint,
        0xc190f1e5 as libc::c_uint,
        0xa1e7438b as libc::c_uint,
        0x7d8ad93c as libc::c_int as libc::c_uint,
        0x61082757 as libc::c_int as libc::c_uint,
        0xbd65bde0 as libc::c_uint,
        0xdd120f8e as libc::c_uint,
        0x17f9539 as libc::c_int as libc::c_uint,
        0xe417f358 as libc::c_uint,
        0x387a69ef as libc::c_int as libc::c_uint,
        0x580ddb81 as libc::c_int as libc::c_uint,
        0x84604136 as libc::c_uint,
        0x98e2bf5d as libc::c_uint,
        0x448f25ea as libc::c_int as libc::c_uint,
        0x24f89784 as libc::c_int as libc::c_uint,
        0xf8950d33 as libc::c_uint,
        0xd1139055 as libc::c_uint,
        0xd7e0ae2 as libc::c_int as libc::c_uint,
        0x6d09b88c as libc::c_int as libc::c_uint,
        0xb164223b as libc::c_uint,
        0xade6dc50 as libc::c_uint,
        0x718b46e7 as libc::c_int as libc::c_uint,
        0x11fcf489 as libc::c_int as libc::c_uint,
        0xcd916e3e as libc::c_uint,
        0x28f9085f as libc::c_int as libc::c_uint,
        0xf49492e8 as libc::c_uint,
        0x94e32086 as libc::c_uint,
        0x488eba31 as libc::c_int as libc::c_uint,
        0x540c445a as libc::c_int as libc::c_uint,
        0x8861deed as libc::c_uint,
        0xe8166c83 as libc::c_uint,
        0x347bf634 as libc::c_int as libc::c_uint,
        0x2607bdf6 as libc::c_int as libc::c_uint,
        0xfa6a2741 as libc::c_uint,
        0x9a1d952f as libc::c_uint,
        0x46700f98 as libc::c_int as libc::c_uint,
        0x5af2f1f3 as libc::c_int as libc::c_uint,
        0x869f6b44 as libc::c_uint,
        0xe6e8d92a as libc::c_uint,
        0x3a85439d as libc::c_int as libc::c_uint,
        0xdfed25fc as libc::c_uint,
        0x380bf4b as libc::c_int as libc::c_uint,
        0x63f70d25 as libc::c_int as libc::c_uint,
        0xbf9a9792 as libc::c_uint,
        0xa31869f9 as libc::c_uint,
        0x7f75f34e as libc::c_int as libc::c_uint,
        0x1f024120 as libc::c_int as libc::c_uint,
        0xc36fdb97 as libc::c_uint,
        0x3bfad6a4 as libc::c_int as libc::c_uint,
        0xe7974c13 as libc::c_uint,
        0x87e0fe7d as libc::c_uint,
        0x5b8d64ca as libc::c_int as libc::c_uint,
        0x470f9aa1 as libc::c_int as libc::c_uint,
        0x9b620016 as libc::c_uint,
        0xfb15b278 as libc::c_uint,
        0x277828cf as libc::c_int as libc::c_uint,
        0xc2104eae as libc::c_uint,
        0x1e7dd419 as libc::c_int as libc::c_uint,
        0x7e0a6677 as libc::c_int as libc::c_uint,
        0xa267fcc0 as libc::c_uint,
        0xbee502ab as libc::c_uint,
        0x6288981c as libc::c_int as libc::c_uint,
        0x2ff2a72 as libc::c_int as libc::c_uint,
        0xde92b0c5 as libc::c_uint,
        0xcceefb07 as libc::c_uint,
        0x108361b0 as libc::c_int as libc::c_uint,
        0x70f4d3de as libc::c_int as libc::c_uint,
        0xac994969 as libc::c_uint,
        0xb01bb702 as libc::c_uint,
        0x6c762db5 as libc::c_int as libc::c_uint,
        0xc019fdb as libc::c_int as libc::c_uint,
        0xd06c056c as libc::c_uint,
        0x3504630d as libc::c_int as libc::c_uint,
        0xe969f9ba as libc::c_uint,
        0x891e4bd4 as libc::c_uint,
        0x5573d163 as libc::c_int as libc::c_uint,
        0x49f12f08 as libc::c_int as libc::c_uint,
        0x959cb5bf as libc::c_uint,
        0xf5eb07d1 as libc::c_uint,
        0x29869d66 as libc::c_int as libc::c_uint,
        0xa6e63d1d as libc::c_uint,
        0x7a8ba7aa as libc::c_int as libc::c_uint,
        0x1afc15c4 as libc::c_int as libc::c_uint,
        0xc6918f73 as libc::c_uint,
        0xda137118 as libc::c_uint,
        0x67eebaf as libc::c_int as libc::c_uint,
        0x660959c1 as libc::c_int as libc::c_uint,
        0xba64c376 as libc::c_uint,
        0x5f0ca517 as libc::c_int as libc::c_uint,
        0x83613fa0 as libc::c_uint,
        0xe3168dce as libc::c_uint,
        0x3f7b1779 as libc::c_int as libc::c_uint,
        0x23f9e912 as libc::c_int as libc::c_uint,
        0xff9473a5 as libc::c_uint,
        0x9fe3c1cb as libc::c_uint,
        0x438e5b7c as libc::c_int as libc::c_uint,
        0x51f210be as libc::c_int as libc::c_uint,
        0x8d9f8a09 as libc::c_uint,
        0xede83867 as libc::c_uint,
        0x3185a2d0 as libc::c_int as libc::c_uint,
        0x2d075cbb as libc::c_int as libc::c_uint,
        0xf16ac60c as libc::c_uint,
        0x911d7462 as libc::c_uint,
        0x4d70eed5 as libc::c_int as libc::c_uint,
        0xa81888b4 as libc::c_uint,
        0x74751203 as libc::c_int as libc::c_uint,
        0x1402a06d as libc::c_int as libc::c_uint,
        0xc86f3ada as libc::c_uint,
        0xd4edc4b1 as libc::c_uint,
        0x8805e06 as libc::c_int as libc::c_uint,
        0x68f7ec68 as libc::c_int as libc::c_uint,
        0xb49a76df as libc::c_uint,
        0x4c0f7bec as libc::c_int as libc::c_uint,
        0x9062e15b as libc::c_uint,
        0xf0155335 as libc::c_uint,
        0x2c78c982 as libc::c_int as libc::c_uint,
        0x30fa37e9 as libc::c_int as libc::c_uint,
        0xec97ad5e as libc::c_uint,
        0x8ce01f30 as libc::c_uint,
        0x508d8587 as libc::c_int as libc::c_uint,
        0xb5e5e3e6 as libc::c_uint,
        0x69887951 as libc::c_int as libc::c_uint,
        0x9ffcb3f as libc::c_int as libc::c_uint,
        0xd5925188 as libc::c_uint,
        0xc910afe3 as libc::c_uint,
        0x157d3554 as libc::c_int as libc::c_uint,
        0x750a873a as libc::c_int as libc::c_uint,
        0xa9671d8d as libc::c_uint,
        0xbb1b564f as libc::c_uint,
        0x6776ccf8 as libc::c_int as libc::c_uint,
        0x7017e96 as libc::c_int as libc::c_uint,
        0xdb6ce421 as libc::c_uint,
        0xc7ee1a4a as libc::c_uint,
        0x1b8380fd as libc::c_int as libc::c_uint,
        0x7bf43293 as libc::c_int as libc::c_uint,
        0xa799a824 as libc::c_uint,
        0x42f1ce45 as libc::c_int as libc::c_uint,
        0x9e9c54f2 as libc::c_uint,
        0xfeebe69c as libc::c_uint,
        0x22867c2b as libc::c_int as libc::c_uint,
        0x3e048240 as libc::c_int as libc::c_uint,
        0xe26918f7 as libc::c_uint,
        0x821eaa99 as libc::c_uint,
        0x5e73302e as libc::c_int as libc::c_uint,
        0x77f5ad48 as libc::c_int as libc::c_uint,
        0xab9837ff as libc::c_uint,
        0xcbef8591 as libc::c_uint,
        0x17821f26 as libc::c_int as libc::c_uint,
        0xb00e14d as libc::c_int as libc::c_uint,
        0xd76d7bfa as libc::c_uint,
        0xb71ac994 as libc::c_uint,
        0x6b775323 as libc::c_int as libc::c_uint,
        0x8e1f3542 as libc::c_uint,
        0x5272aff5 as libc::c_int as libc::c_uint,
        0x32051d9b as libc::c_int as libc::c_uint,
        0xee68872c as libc::c_uint,
        0xf2ea7947 as libc::c_uint,
        0x2e87e3f0 as libc::c_int as libc::c_uint,
        0x4ef0519e as libc::c_int as libc::c_uint,
        0x929dcb29 as libc::c_uint,
        0x80e180eb as libc::c_uint,
        0x5c8c1a5c as libc::c_int as libc::c_uint,
        0x3cfba832 as libc::c_int as libc::c_uint,
        0xe0963285 as libc::c_uint,
        0xfc14ccee as libc::c_uint,
        0x20795659 as libc::c_int as libc::c_uint,
        0x400ee437 as libc::c_int as libc::c_uint,
        0x9c637e80 as libc::c_uint,
        0x790b18e1 as libc::c_int as libc::c_uint,
        0xa5668256 as libc::c_uint,
        0xc5113038 as libc::c_uint,
        0x197caa8f as libc::c_int as libc::c_uint,
        0x5fe54e4 as libc::c_int as libc::c_uint,
        0xd993ce53 as libc::c_uint,
        0xb9e47c3d as libc::c_uint,
        0x6589e68a as libc::c_int as libc::c_uint,
        0x9d1cebb9 as libc::c_uint,
        0x4171710e as libc::c_int as libc::c_uint,
        0x2106c360 as libc::c_int as libc::c_uint,
        0xfd6b59d7 as libc::c_uint,
        0xe1e9a7bc as libc::c_uint,
        0x3d843d0b as libc::c_int as libc::c_uint,
        0x5df38f65 as libc::c_int as libc::c_uint,
        0x819e15d2 as libc::c_uint,
        0x64f673b3 as libc::c_int as libc::c_uint,
        0xb89be904 as libc::c_uint,
        0xd8ec5b6a as libc::c_uint,
        0x481c1dd as libc::c_int as libc::c_uint,
        0x18033fb6 as libc::c_int as libc::c_uint,
        0xc46ea501 as libc::c_uint,
        0xa419176f as libc::c_uint,
        0x78748dd8 as libc::c_int as libc::c_uint,
        0x6a08c61a as libc::c_int as libc::c_uint,
        0xb6655cad as libc::c_uint,
        0xd612eec3 as libc::c_uint,
        0xa7f7474 as libc::c_int as libc::c_uint,
        0x16fd8a1f as libc::c_int as libc::c_uint,
        0xca9010a8 as libc::c_uint,
        0xaae7a2c6 as libc::c_uint,
        0x768a3871 as libc::c_int as libc::c_uint,
        0x93e25e10 as libc::c_uint,
        0x4f8fc4a7 as libc::c_int as libc::c_uint,
        0x2ff876c9 as libc::c_int as libc::c_uint,
        0xf395ec7e as libc::c_uint,
        0xef171215 as libc::c_uint,
        0x337a88a2 as libc::c_int as libc::c_uint,
        0x530d3acc as libc::c_int as libc::c_uint,
        0x8f60a07b as libc::c_uint,
    ],
    [
        0 as libc::c_int as libc::c_uint,
        0x490d678d as libc::c_int as libc::c_uint,
        0x921acf1a as libc::c_uint,
        0xdb17a897 as libc::c_uint,
        0x20f48383 as libc::c_int as libc::c_uint,
        0x69f9e40e as libc::c_int as libc::c_uint,
        0xb2ee4c99 as libc::c_uint,
        0xfbe32b14 as libc::c_uint,
        0x41e90706 as libc::c_int as libc::c_uint,
        0x8e4608b as libc::c_int as libc::c_uint,
        0xd3f3c81c as libc::c_uint,
        0x9afeaf91 as libc::c_uint,
        0x611d8485 as libc::c_int as libc::c_uint,
        0x2810e308 as libc::c_int as libc::c_uint,
        0xf3074b9f as libc::c_uint,
        0xba0a2c12 as libc::c_uint,
        0x83d20e0c as libc::c_uint,
        0xcadf6981 as libc::c_uint,
        0x11c8c116 as libc::c_int as libc::c_uint,
        0x58c5a69b as libc::c_int as libc::c_uint,
        0xa3268d8f as libc::c_uint,
        0xea2bea02 as libc::c_uint,
        0x313c4295 as libc::c_int as libc::c_uint,
        0x78312518 as libc::c_int as libc::c_uint,
        0xc23b090a as libc::c_uint,
        0x8b366e87 as libc::c_uint,
        0x5021c610 as libc::c_int as libc::c_uint,
        0x192ca19d as libc::c_int as libc::c_uint,
        0xe2cf8a89 as libc::c_uint,
        0xabc2ed04 as libc::c_uint,
        0x70d54593 as libc::c_int as libc::c_uint,
        0x39d8221e as libc::c_int as libc::c_uint,
        0x36501af as libc::c_int as libc::c_uint,
        0x4a686622 as libc::c_int as libc::c_uint,
        0x917fceb5 as libc::c_uint,
        0xd872a938 as libc::c_uint,
        0x2391822c as libc::c_int as libc::c_uint,
        0x6a9ce5a1 as libc::c_int as libc::c_uint,
        0xb18b4d36 as libc::c_uint,
        0xf8862abb as libc::c_uint,
        0x428c06a9 as libc::c_int as libc::c_uint,
        0xb816124 as libc::c_int as libc::c_uint,
        0xd096c9b3 as libc::c_uint,
        0x999bae3e as libc::c_uint,
        0x6278852a as libc::c_int as libc::c_uint,
        0x2b75e2a7 as libc::c_int as libc::c_uint,
        0xf0624a30 as libc::c_uint,
        0xb96f2dbd as libc::c_uint,
        0x80b70fa3 as libc::c_uint,
        0xc9ba682e as libc::c_uint,
        0x12adc0b9 as libc::c_int as libc::c_uint,
        0x5ba0a734 as libc::c_int as libc::c_uint,
        0xa0438c20 as libc::c_uint,
        0xe94eebad as libc::c_uint,
        0x3259433a as libc::c_int as libc::c_uint,
        0x7b5424b7 as libc::c_int as libc::c_uint,
        0xc15e08a5 as libc::c_uint,
        0x88536f28 as libc::c_uint,
        0x5344c7bf as libc::c_int as libc::c_uint,
        0x1a49a032 as libc::c_int as libc::c_uint,
        0xe1aa8b26 as libc::c_uint,
        0xa8a7ecab as libc::c_uint,
        0x73b0443c as libc::c_int as libc::c_uint,
        0x3abd23b1 as libc::c_int as libc::c_uint,
        0x6ca035e as libc::c_int as libc::c_uint,
        0x4fc764d3 as libc::c_int as libc::c_uint,
        0x94d0cc44 as libc::c_uint,
        0xddddabc9 as libc::c_uint,
        0x263e80dd as libc::c_int as libc::c_uint,
        0x6f33e750 as libc::c_int as libc::c_uint,
        0xb4244fc7 as libc::c_uint,
        0xfd29284a as libc::c_uint,
        0x47230458 as libc::c_int as libc::c_uint,
        0xe2e63d5 as libc::c_int as libc::c_uint,
        0xd539cb42 as libc::c_uint,
        0x9c34accf as libc::c_uint,
        0x67d787db as libc::c_int as libc::c_uint,
        0x2edae056 as libc::c_int as libc::c_uint,
        0xf5cd48c1 as libc::c_uint,
        0xbcc02f4c as libc::c_uint,
        0x85180d52 as libc::c_uint,
        0xcc156adf as libc::c_uint,
        0x1702c248 as libc::c_int as libc::c_uint,
        0x5e0fa5c5 as libc::c_int as libc::c_uint,
        0xa5ec8ed1 as libc::c_uint,
        0xece1e95c as libc::c_uint,
        0x37f641cb as libc::c_int as libc::c_uint,
        0x7efb2646 as libc::c_int as libc::c_uint,
        0xc4f10a54 as libc::c_uint,
        0x8dfc6dd9 as libc::c_uint,
        0x56ebc54e as libc::c_int as libc::c_uint,
        0x1fe6a2c3 as libc::c_int as libc::c_uint,
        0xe40589d7 as libc::c_uint,
        0xad08ee5a as libc::c_uint,
        0x761f46cd as libc::c_int as libc::c_uint,
        0x3f122140 as libc::c_int as libc::c_uint,
        0x5af02f1 as libc::c_int as libc::c_uint,
        0x4ca2657c as libc::c_int as libc::c_uint,
        0x97b5cdeb as libc::c_uint,
        0xdeb8aa66 as libc::c_uint,
        0x255b8172 as libc::c_int as libc::c_uint,
        0x6c56e6ff as libc::c_int as libc::c_uint,
        0xb7414e68 as libc::c_uint,
        0xfe4c29e5 as libc::c_uint,
        0x444605f7 as libc::c_int as libc::c_uint,
        0xd4b627a as libc::c_int as libc::c_uint,
        0xd65ccaed as libc::c_uint,
        0x9f51ad60 as libc::c_uint,
        0x64b28674 as libc::c_int as libc::c_uint,
        0x2dbfe1f9 as libc::c_int as libc::c_uint,
        0xf6a8496e as libc::c_uint,
        0xbfa52ee3 as libc::c_uint,
        0x867d0cfd as libc::c_uint,
        0xcf706b70 as libc::c_uint,
        0x1467c3e7 as libc::c_int as libc::c_uint,
        0x5d6aa46a as libc::c_int as libc::c_uint,
        0xa6898f7e as libc::c_uint,
        0xef84e8f3 as libc::c_uint,
        0x34934064 as libc::c_int as libc::c_uint,
        0x7d9e27e9 as libc::c_int as libc::c_uint,
        0xc7940bfb as libc::c_uint,
        0x8e996c76 as libc::c_uint,
        0x558ec4e1 as libc::c_int as libc::c_uint,
        0x1c83a36c as libc::c_int as libc::c_uint,
        0xe7608878 as libc::c_uint,
        0xae6deff5 as libc::c_uint,
        0x757a4762 as libc::c_int as libc::c_uint,
        0x3c7720ef as libc::c_int as libc::c_uint,
        0xd9406bc as libc::c_int as libc::c_uint,
        0x44996131 as libc::c_int as libc::c_uint,
        0x9f8ec9a6 as libc::c_uint,
        0xd683ae2b as libc::c_uint,
        0x2d60853f as libc::c_int as libc::c_uint,
        0x646de2b2 as libc::c_int as libc::c_uint,
        0xbf7a4a25 as libc::c_uint,
        0xf6772da8 as libc::c_uint,
        0x4c7d01ba as libc::c_int as libc::c_uint,
        0x5706637 as libc::c_int as libc::c_uint,
        0xde67cea0 as libc::c_uint,
        0x976aa92d as libc::c_uint,
        0x6c898239 as libc::c_int as libc::c_uint,
        0x2584e5b4 as libc::c_int as libc::c_uint,
        0xfe934d23 as libc::c_uint,
        0xb79e2aae as libc::c_uint,
        0x8e4608b0 as libc::c_uint,
        0xc74b6f3d as libc::c_uint,
        0x1c5cc7aa as libc::c_int as libc::c_uint,
        0x5551a027 as libc::c_int as libc::c_uint,
        0xaeb28b33 as libc::c_uint,
        0xe7bfecbe as libc::c_uint,
        0x3ca84429 as libc::c_int as libc::c_uint,
        0x75a523a4 as libc::c_int as libc::c_uint,
        0xcfaf0fb6 as libc::c_uint,
        0x86a2683b as libc::c_uint,
        0x5db5c0ac as libc::c_int as libc::c_uint,
        0x14b8a721 as libc::c_int as libc::c_uint,
        0xef5b8c35 as libc::c_uint,
        0xa656ebb8 as libc::c_uint,
        0x7d41432f as libc::c_int as libc::c_uint,
        0x344c24a2 as libc::c_int as libc::c_uint,
        0xef10713 as libc::c_int as libc::c_uint,
        0x47fc609e as libc::c_int as libc::c_uint,
        0x9cebc809 as libc::c_uint,
        0xd5e6af84 as libc::c_uint,
        0x2e058490 as libc::c_int as libc::c_uint,
        0x6708e31d as libc::c_int as libc::c_uint,
        0xbc1f4b8a as libc::c_uint,
        0xf5122c07 as libc::c_uint,
        0x4f180015 as libc::c_int as libc::c_uint,
        0x6156798 as libc::c_int as libc::c_uint,
        0xdd02cf0f as libc::c_uint,
        0x940fa882 as libc::c_uint,
        0x6fec8396 as libc::c_int as libc::c_uint,
        0x26e1e41b as libc::c_int as libc::c_uint,
        0xfdf64c8c as libc::c_uint,
        0xb4fb2b01 as libc::c_uint,
        0x8d23091f as libc::c_uint,
        0xc42e6e92 as libc::c_uint,
        0x1f39c605 as libc::c_int as libc::c_uint,
        0x5634a188 as libc::c_int as libc::c_uint,
        0xadd78a9c as libc::c_uint,
        0xe4daed11 as libc::c_uint,
        0x3fcd4586 as libc::c_int as libc::c_uint,
        0x76c0220b as libc::c_int as libc::c_uint,
        0xccca0e19 as libc::c_uint,
        0x85c76994 as libc::c_uint,
        0x5ed0c103 as libc::c_int as libc::c_uint,
        0x17dda68e as libc::c_int as libc::c_uint,
        0xec3e8d9a as libc::c_uint,
        0xa533ea17 as libc::c_uint,
        0x7e244280 as libc::c_int as libc::c_uint,
        0x3729250d as libc::c_int as libc::c_uint,
        0xb5e05e2 as libc::c_int as libc::c_uint,
        0x4253626f as libc::c_int as libc::c_uint,
        0x9944caf8 as libc::c_uint,
        0xd049ad75 as libc::c_uint,
        0x2baa8661 as libc::c_int as libc::c_uint,
        0x62a7e1ec as libc::c_int as libc::c_uint,
        0xb9b0497b as libc::c_uint,
        0xf0bd2ef6 as libc::c_uint,
        0x4ab702e4 as libc::c_int as libc::c_uint,
        0x3ba6569 as libc::c_int as libc::c_uint,
        0xd8adcdfe as libc::c_uint,
        0x91a0aa73 as libc::c_uint,
        0x6a438167 as libc::c_int as libc::c_uint,
        0x234ee6ea as libc::c_int as libc::c_uint,
        0xf8594e7d as libc::c_uint,
        0xb15429f0 as libc::c_uint,
        0x888c0bee as libc::c_uint,
        0xc1816c63 as libc::c_uint,
        0x1a96c4f4 as libc::c_int as libc::c_uint,
        0x539ba379 as libc::c_int as libc::c_uint,
        0xa878886d as libc::c_uint,
        0xe175efe0 as libc::c_uint,
        0x3a624777 as libc::c_int as libc::c_uint,
        0x736f20fa as libc::c_int as libc::c_uint,
        0xc9650ce8 as libc::c_uint,
        0x80686b65 as libc::c_uint,
        0x5b7fc3f2 as libc::c_int as libc::c_uint,
        0x1272a47f as libc::c_int as libc::c_uint,
        0xe9918f6b as libc::c_uint,
        0xa09ce8e6 as libc::c_uint,
        0x7b8b4071 as libc::c_int as libc::c_uint,
        0x328627fc as libc::c_int as libc::c_uint,
        0x83b044d as libc::c_int as libc::c_uint,
        0x413663c0 as libc::c_int as libc::c_uint,
        0x9a21cb57 as libc::c_uint,
        0xd32cacda as libc::c_uint,
        0x28cf87ce as libc::c_int as libc::c_uint,
        0x61c2e043 as libc::c_int as libc::c_uint,
        0xbad548d4 as libc::c_uint,
        0xf3d82f59 as libc::c_uint,
        0x49d2034b as libc::c_int as libc::c_uint,
        0xdf64c6 as libc::c_int as libc::c_uint,
        0xdbc8cc51 as libc::c_uint,
        0x92c5abdc as libc::c_uint,
        0x692680c8 as libc::c_int as libc::c_uint,
        0x202be745 as libc::c_int as libc::c_uint,
        0xfb3c4fd2 as libc::c_uint,
        0xb231285f as libc::c_uint,
        0x8be90a41 as libc::c_uint,
        0xc2e46dcc as libc::c_uint,
        0x19f3c55b as libc::c_int as libc::c_uint,
        0x50fea2d6 as libc::c_int as libc::c_uint,
        0xab1d89c2 as libc::c_uint,
        0xe210ee4f as libc::c_uint,
        0x390746d8 as libc::c_int as libc::c_uint,
        0x700a2155 as libc::c_int as libc::c_uint,
        0xca000d47 as libc::c_uint,
        0x830d6aca as libc::c_uint,
        0x581ac25d as libc::c_int as libc::c_uint,
        0x1117a5d0 as libc::c_int as libc::c_uint,
        0xeaf48ec4 as libc::c_uint,
        0xa3f9e949 as libc::c_uint,
        0x78ee41de as libc::c_int as libc::c_uint,
        0x31e32653 as libc::c_int as libc::c_uint,
    ],
    [
        0 as libc::c_int as libc::c_uint,
        0x1b280d78 as libc::c_int as libc::c_uint,
        0x36501af0 as libc::c_int as libc::c_uint,
        0x2d781788 as libc::c_int as libc::c_uint,
        0x6ca035e0 as libc::c_int as libc::c_uint,
        0x77883898 as libc::c_int as libc::c_uint,
        0x5af02f10 as libc::c_int as libc::c_uint,
        0x41d82268 as libc::c_int as libc::c_uint,
        0xd9406bc0 as libc::c_uint,
        0xc26866b8 as libc::c_uint,
        0xef107130 as libc::c_uint,
        0xf4387c48 as libc::c_uint,
        0xb5e05e20 as libc::c_uint,
        0xaec85358 as libc::c_uint,
        0x83b044d0 as libc::c_uint,
        0x989849a8 as libc::c_uint,
        0xb641ca37 as libc::c_uint,
        0xad69c74f as libc::c_uint,
        0x8011d0c7 as libc::c_uint,
        0x9b39ddbf as libc::c_uint,
        0xdae1ffd7 as libc::c_uint,
        0xc1c9f2af as libc::c_uint,
        0xecb1e527 as libc::c_uint,
        0xf799e85f as libc::c_uint,
        0x6f01a1f7 as libc::c_int as libc::c_uint,
        0x7429ac8f as libc::c_int as libc::c_uint,
        0x5951bb07 as libc::c_int as libc::c_uint,
        0x4279b67f as libc::c_int as libc::c_uint,
        0x3a19417 as libc::c_int as libc::c_uint,
        0x1889996f as libc::c_int as libc::c_uint,
        0x35f18ee7 as libc::c_int as libc::c_uint,
        0x2ed9839f as libc::c_int as libc::c_uint,
        0x684289d9 as libc::c_int as libc::c_uint,
        0x736a84a1 as libc::c_int as libc::c_uint,
        0x5e129329 as libc::c_int as libc::c_uint,
        0x453a9e51 as libc::c_int as libc::c_uint,
        0x4e2bc39 as libc::c_int as libc::c_uint,
        0x1fcab141 as libc::c_int as libc::c_uint,
        0x32b2a6c9 as libc::c_int as libc::c_uint,
        0x299aabb1 as libc::c_int as libc::c_uint,
        0xb102e219 as libc::c_uint,
        0xaa2aef61 as libc::c_uint,
        0x8752f8e9 as libc::c_uint,
        0x9c7af591 as libc::c_uint,
        0xdda2d7f9 as libc::c_uint,
        0xc68ada81 as libc::c_uint,
        0xebf2cd09 as libc::c_uint,
        0xf0dac071 as libc::c_uint,
        0xde0343ee as libc::c_uint,
        0xc52b4e96 as libc::c_uint,
        0xe853591e as libc::c_uint,
        0xf37b5466 as libc::c_uint,
        0xb2a3760e as libc::c_uint,
        0xa98b7b76 as libc::c_uint,
        0x84f36cfe as libc::c_uint,
        0x9fdb6186 as libc::c_uint,
        0x743282e as libc::c_int as libc::c_uint,
        0x1c6b2556 as libc::c_int as libc::c_uint,
        0x311332de as libc::c_int as libc::c_uint,
        0x2a3b3fa6 as libc::c_int as libc::c_uint,
        0x6be31dce as libc::c_int as libc::c_uint,
        0x70cb10b6 as libc::c_int as libc::c_uint,
        0x5db3073e as libc::c_int as libc::c_uint,
        0x469b0a46 as libc::c_int as libc::c_uint,
        0xd08513b2 as libc::c_uint,
        0xcbad1eca as libc::c_uint,
        0xe6d50942 as libc::c_uint,
        0xfdfd043a as libc::c_uint,
        0xbc252652 as libc::c_uint,
        0xa70d2b2a as libc::c_uint,
        0x8a753ca2 as libc::c_uint,
        0x915d31da as libc::c_uint,
        0x9c57872 as libc::c_int as libc::c_uint,
        0x12ed750a as libc::c_int as libc::c_uint,
        0x3f956282 as libc::c_int as libc::c_uint,
        0x24bd6ffa as libc::c_int as libc::c_uint,
        0x65654d92 as libc::c_int as libc::c_uint,
        0x7e4d40ea as libc::c_int as libc::c_uint,
        0x53355762 as libc::c_int as libc::c_uint,
        0x481d5a1a as libc::c_int as libc::c_uint,
        0x66c4d985 as libc::c_int as libc::c_uint,
        0x7decd4fd as libc::c_int as libc::c_uint,
        0x5094c375 as libc::c_int as libc::c_uint,
        0x4bbcce0d as libc::c_int as libc::c_uint,
        0xa64ec65 as libc::c_int as libc::c_uint,
        0x114ce11d as libc::c_int as libc::c_uint,
        0x3c34f695 as libc::c_int as libc::c_uint,
        0x271cfbed as libc::c_int as libc::c_uint,
        0xbf84b245 as libc::c_uint,
        0xa4acbf3d as libc::c_uint,
        0x89d4a8b5 as libc::c_uint,
        0x92fca5cd as libc::c_uint,
        0xd32487a5 as libc::c_uint,
        0xc80c8add as libc::c_uint,
        0xe5749d55 as libc::c_uint,
        0xfe5c902d as libc::c_uint,
        0xb8c79a6b as libc::c_uint,
        0xa3ef9713 as libc::c_uint,
        0x8e97809b as libc::c_uint,
        0x95bf8de3 as libc::c_uint,
        0xd467af8b as libc::c_uint,
        0xcf4fa2f3 as libc::c_uint,
        0xe237b57b as libc::c_uint,
        0xf91fb803 as libc::c_uint,
        0x6187f1ab as libc::c_int as libc::c_uint,
        0x7aaffcd3 as libc::c_int as libc::c_uint,
        0x57d7eb5b as libc::c_int as libc::c_uint,
        0x4cffe623 as libc::c_int as libc::c_uint,
        0xd27c44b as libc::c_int as libc::c_uint,
        0x160fc933 as libc::c_int as libc::c_uint,
        0x3b77debb as libc::c_int as libc::c_uint,
        0x205fd3c3 as libc::c_int as libc::c_uint,
        0xe86505c as libc::c_int as libc::c_uint,
        0x15ae5d24 as libc::c_int as libc::c_uint,
        0x38d64aac as libc::c_int as libc::c_uint,
        0x23fe47d4 as libc::c_int as libc::c_uint,
        0x622665bc as libc::c_int as libc::c_uint,
        0x790e68c4 as libc::c_int as libc::c_uint,
        0x54767f4c as libc::c_int as libc::c_uint,
        0x4f5e7234 as libc::c_int as libc::c_uint,
        0xd7c63b9c as libc::c_uint,
        0xccee36e4 as libc::c_uint,
        0xe196216c as libc::c_uint,
        0xfabe2c14 as libc::c_uint,
        0xbb660e7c as libc::c_uint,
        0xa04e0304 as libc::c_uint,
        0x8d36148c as libc::c_uint,
        0x961e19f4 as libc::c_uint,
        0xa5cb3ad3 as libc::c_uint,
        0xbee337ab as libc::c_uint,
        0x939b2023 as libc::c_uint,
        0x88b32d5b as libc::c_uint,
        0xc96b0f33 as libc::c_uint,
        0xd243024b as libc::c_uint,
        0xff3b15c3 as libc::c_uint,
        0xe41318bb as libc::c_uint,
        0x7c8b5113 as libc::c_int as libc::c_uint,
        0x67a35c6b as libc::c_int as libc::c_uint,
        0x4adb4be3 as libc::c_int as libc::c_uint,
        0x51f3469b as libc::c_int as libc::c_uint,
        0x102b64f3 as libc::c_int as libc::c_uint,
        0xb03698b as libc::c_int as libc::c_uint,
        0x267b7e03 as libc::c_int as libc::c_uint,
        0x3d53737b as libc::c_int as libc::c_uint,
        0x138af0e4 as libc::c_int as libc::c_uint,
        0x8a2fd9c as libc::c_int as libc::c_uint,
        0x25daea14 as libc::c_int as libc::c_uint,
        0x3ef2e76c as libc::c_int as libc::c_uint,
        0x7f2ac504 as libc::c_int as libc::c_uint,
        0x6402c87c as libc::c_int as libc::c_uint,
        0x497adff4 as libc::c_int as libc::c_uint,
        0x5252d28c as libc::c_int as libc::c_uint,
        0xcaca9b24 as libc::c_uint,
        0xd1e2965c as libc::c_uint,
        0xfc9a81d4 as libc::c_uint,
        0xe7b28cac as libc::c_uint,
        0xa66aaec4 as libc::c_uint,
        0xbd42a3bc as libc::c_uint,
        0x903ab434 as libc::c_uint,
        0x8b12b94c as libc::c_uint,
        0xcd89b30a as libc::c_uint,
        0xd6a1be72 as libc::c_uint,
        0xfbd9a9fa as libc::c_uint,
        0xe0f1a482 as libc::c_uint,
        0xa12986ea as libc::c_uint,
        0xba018b92 as libc::c_uint,
        0x97799c1a as libc::c_uint,
        0x8c519162 as libc::c_uint,
        0x14c9d8ca as libc::c_int as libc::c_uint,
        0xfe1d5b2 as libc::c_int as libc::c_uint,
        0x2299c23a as libc::c_int as libc::c_uint,
        0x39b1cf42 as libc::c_int as libc::c_uint,
        0x7869ed2a as libc::c_int as libc::c_uint,
        0x6341e052 as libc::c_int as libc::c_uint,
        0x4e39f7da as libc::c_int as libc::c_uint,
        0x5511faa2 as libc::c_int as libc::c_uint,
        0x7bc8793d as libc::c_int as libc::c_uint,
        0x60e07445 as libc::c_int as libc::c_uint,
        0x4d9863cd as libc::c_int as libc::c_uint,
        0x56b06eb5 as libc::c_int as libc::c_uint,
        0x17684cdd as libc::c_int as libc::c_uint,
        0xc4041a5 as libc::c_int as libc::c_uint,
        0x2138562d as libc::c_int as libc::c_uint,
        0x3a105b55 as libc::c_int as libc::c_uint,
        0xa28812fd as libc::c_uint,
        0xb9a01f85 as libc::c_uint,
        0x94d8080d as libc::c_uint,
        0x8ff00575 as libc::c_uint,
        0xce28271d as libc::c_uint,
        0xd5002a65 as libc::c_uint,
        0xf8783ded as libc::c_uint,
        0xe3503095 as libc::c_uint,
        0x754e2961 as libc::c_int as libc::c_uint,
        0x6e662419 as libc::c_int as libc::c_uint,
        0x431e3391 as libc::c_int as libc::c_uint,
        0x58363ee9 as libc::c_int as libc::c_uint,
        0x19ee1c81 as libc::c_int as libc::c_uint,
        0x2c611f9 as libc::c_int as libc::c_uint,
        0x2fbe0671 as libc::c_int as libc::c_uint,
        0x34960b09 as libc::c_int as libc::c_uint,
        0xac0e42a1 as libc::c_uint,
        0xb7264fd9 as libc::c_uint,
        0x9a5e5851 as libc::c_uint,
        0x81765529 as libc::c_uint,
        0xc0ae7741 as libc::c_uint,
        0xdb867a39 as libc::c_uint,
        0xf6fe6db1 as libc::c_uint,
        0xedd660c9 as libc::c_uint,
        0xc30fe356 as libc::c_uint,
        0xd827ee2e as libc::c_uint,
        0xf55ff9a6 as libc::c_uint,
        0xee77f4de as libc::c_uint,
        0xafafd6b6 as libc::c_uint,
        0xb487dbce as libc::c_uint,
        0x99ffcc46 as libc::c_uint,
        0x82d7c13e as libc::c_uint,
        0x1a4f8896 as libc::c_int as libc::c_uint,
        0x16785ee as libc::c_int as libc::c_uint,
        0x2c1f9266 as libc::c_int as libc::c_uint,
        0x37379f1e as libc::c_int as libc::c_uint,
        0x76efbd76 as libc::c_int as libc::c_uint,
        0x6dc7b00e as libc::c_int as libc::c_uint,
        0x40bfa786 as libc::c_int as libc::c_uint,
        0x5b97aafe as libc::c_int as libc::c_uint,
        0x1d0ca0b8 as libc::c_int as libc::c_uint,
        0x624adc0 as libc::c_int as libc::c_uint,
        0x2b5cba48 as libc::c_int as libc::c_uint,
        0x3074b730 as libc::c_int as libc::c_uint,
        0x71ac9558 as libc::c_int as libc::c_uint,
        0x6a849820 as libc::c_int as libc::c_uint,
        0x47fc8fa8 as libc::c_int as libc::c_uint,
        0x5cd482d0 as libc::c_int as libc::c_uint,
        0xc44ccb78 as libc::c_uint,
        0xdf64c600 as libc::c_uint,
        0xf21cd188 as libc::c_uint,
        0xe934dcf0 as libc::c_uint,
        0xa8ecfe98 as libc::c_uint,
        0xb3c4f3e0 as libc::c_uint,
        0x9ebce468 as libc::c_uint,
        0x8594e910 as libc::c_uint,
        0xab4d6a8f as libc::c_uint,
        0xb06567f7 as libc::c_uint,
        0x9d1d707f as libc::c_uint,
        0x86357d07 as libc::c_uint,
        0xc7ed5f6f as libc::c_uint,
        0xdcc55217 as libc::c_uint,
        0xf1bd459f as libc::c_uint,
        0xea9548e7 as libc::c_uint,
        0x720d014f as libc::c_int as libc::c_uint,
        0x69250c37 as libc::c_int as libc::c_uint,
        0x445d1bbf as libc::c_int as libc::c_uint,
        0x5f7516c7 as libc::c_int as libc::c_uint,
        0x1ead34af as libc::c_int as libc::c_uint,
        0x58539d7 as libc::c_int as libc::c_uint,
        0x28fd2e5f as libc::c_int as libc::c_uint,
        0x33d52327 as libc::c_int as libc::c_uint,
    ],
    [
        0 as libc::c_int as libc::c_uint,
        0x4f576811 as libc::c_int as libc::c_uint,
        0x9eaed022 as libc::c_uint,
        0xd1f9b833 as libc::c_uint,
        0x399cbdf3 as libc::c_int as libc::c_uint,
        0x76cbd5e2 as libc::c_int as libc::c_uint,
        0xa7326dd1 as libc::c_uint,
        0xe86505c0 as libc::c_uint,
        0x73397be6 as libc::c_int as libc::c_uint,
        0x3c6e13f7 as libc::c_int as libc::c_uint,
        0xed97abc4 as libc::c_uint,
        0xa2c0c3d5 as libc::c_uint,
        0x4aa5c615 as libc::c_int as libc::c_uint,
        0x5f2ae04 as libc::c_int as libc::c_uint,
        0xd40b1637 as libc::c_uint,
        0x9b5c7e26 as libc::c_uint,
        0xe672f7cc as libc::c_uint,
        0xa9259fdd as libc::c_uint,
        0x78dc27ee as libc::c_int as libc::c_uint,
        0x378b4fff as libc::c_int as libc::c_uint,
        0xdfee4a3f as libc::c_uint,
        0x90b9222e as libc::c_uint,
        0x41409a1d as libc::c_int as libc::c_uint,
        0xe17f20c as libc::c_int as libc::c_uint,
        0x954b8c2a as libc::c_uint,
        0xda1ce43b as libc::c_uint,
        0xbe55c08 as libc::c_int as libc::c_uint,
        0x44b23419 as libc::c_int as libc::c_uint,
        0xacd731d9 as libc::c_uint,
        0xe38059c8 as libc::c_uint,
        0x3279e1fb as libc::c_int as libc::c_uint,
        0x7d2e89ea as libc::c_int as libc::c_uint,
        0xc824f22f as libc::c_uint,
        0x87739a3e as libc::c_uint,
        0x568a220d as libc::c_int as libc::c_uint,
        0x19dd4a1c as libc::c_int as libc::c_uint,
        0xf1b84fdc as libc::c_uint,
        0xbeef27cd as libc::c_uint,
        0x6f169ffe as libc::c_int as libc::c_uint,
        0x2041f7ef as libc::c_int as libc::c_uint,
        0xbb1d89c9 as libc::c_uint,
        0xf44ae1d8 as libc::c_uint,
        0x25b359eb as libc::c_int as libc::c_uint,
        0x6ae431fa as libc::c_int as libc::c_uint,
        0x8281343a as libc::c_uint,
        0xcdd65c2b as libc::c_uint,
        0x1c2fe418 as libc::c_int as libc::c_uint,
        0x53788c09 as libc::c_int as libc::c_uint,
        0x2e5605e3 as libc::c_int as libc::c_uint,
        0x61016df2 as libc::c_int as libc::c_uint,
        0xb0f8d5c1 as libc::c_uint,
        0xffafbdd0 as libc::c_uint,
        0x17cab810 as libc::c_int as libc::c_uint,
        0x589dd001 as libc::c_int as libc::c_uint,
        0x89646832 as libc::c_uint,
        0xc6330023 as libc::c_uint,
        0x5d6f7e05 as libc::c_int as libc::c_uint,
        0x12381614 as libc::c_int as libc::c_uint,
        0xc3c1ae27 as libc::c_uint,
        0x8c96c636 as libc::c_uint,
        0x64f3c3f6 as libc::c_int as libc::c_uint,
        0x2ba4abe7 as libc::c_int as libc::c_uint,
        0xfa5d13d4 as libc::c_uint,
        0xb50a7bc5 as libc::c_uint,
        0x9488f9e9 as libc::c_uint,
        0xdbdf91f8 as libc::c_uint,
        0xa2629cb as libc::c_int as libc::c_uint,
        0x457141da as libc::c_int as libc::c_uint,
        0xad14441a as libc::c_uint,
        0xe2432c0b as libc::c_uint,
        0x33ba9438 as libc::c_int as libc::c_uint,
        0x7cedfc29 as libc::c_int as libc::c_uint,
        0xe7b1820f as libc::c_uint,
        0xa8e6ea1e as libc::c_uint,
        0x791f522d as libc::c_int as libc::c_uint,
        0x36483a3c as libc::c_int as libc::c_uint,
        0xde2d3ffc as libc::c_uint,
        0x917a57ed as libc::c_uint,
        0x4083efde as libc::c_int as libc::c_uint,
        0xfd487cf as libc::c_int as libc::c_uint,
        0x72fa0e25 as libc::c_int as libc::c_uint,
        0x3dad6634 as libc::c_int as libc::c_uint,
        0xec54de07 as libc::c_uint,
        0xa303b616 as libc::c_uint,
        0x4b66b3d6 as libc::c_int as libc::c_uint,
        0x431dbc7 as libc::c_int as libc::c_uint,
        0xd5c863f4 as libc::c_uint,
        0x9a9f0be5 as libc::c_uint,
        0x1c375c3 as libc::c_int as libc::c_uint,
        0x4e941dd2 as libc::c_int as libc::c_uint,
        0x9f6da5e1 as libc::c_uint,
        0xd03acdf0 as libc::c_uint,
        0x385fc830 as libc::c_int as libc::c_uint,
        0x7708a021 as libc::c_int as libc::c_uint,
        0xa6f11812 as libc::c_uint,
        0xe9a67003 as libc::c_uint,
        0x5cac0bc6 as libc::c_int as libc::c_uint,
        0x13fb63d7 as libc::c_int as libc::c_uint,
        0xc202dbe4 as libc::c_uint,
        0x8d55b3f5 as libc::c_uint,
        0x6530b635 as libc::c_int as libc::c_uint,
        0x2a67de24 as libc::c_int as libc::c_uint,
        0xfb9e6617 as libc::c_uint,
        0xb4c90e06 as libc::c_uint,
        0x2f957020 as libc::c_int as libc::c_uint,
        0x60c21831 as libc::c_int as libc::c_uint,
        0xb13ba002 as libc::c_uint,
        0xfe6cc813 as libc::c_uint,
        0x1609cdd3 as libc::c_int as libc::c_uint,
        0x595ea5c2 as libc::c_int as libc::c_uint,
        0x88a71df1 as libc::c_uint,
        0xc7f075e0 as libc::c_uint,
        0xbadefc0a as libc::c_uint,
        0xf589941b as libc::c_uint,
        0x24702c28 as libc::c_int as libc::c_uint,
        0x6b274439 as libc::c_int as libc::c_uint,
        0x834241f9 as libc::c_uint,
        0xcc1529e8 as libc::c_uint,
        0x1dec91db as libc::c_int as libc::c_uint,
        0x52bbf9ca as libc::c_int as libc::c_uint,
        0xc9e787ec as libc::c_uint,
        0x86b0effd as libc::c_uint,
        0x574957ce as libc::c_int as libc::c_uint,
        0x181e3fdf as libc::c_int as libc::c_uint,
        0xf07b3a1f as libc::c_uint,
        0xbf2c520e as libc::c_uint,
        0x6ed5ea3d as libc::c_int as libc::c_uint,
        0x2182822c as libc::c_int as libc::c_uint,
        0x2dd0ee65 as libc::c_int as libc::c_uint,
        0x62878674 as libc::c_int as libc::c_uint,
        0xb37e3e47 as libc::c_uint,
        0xfc295656 as libc::c_uint,
        0x144c5396 as libc::c_int as libc::c_uint,
        0x5b1b3b87 as libc::c_int as libc::c_uint,
        0x8ae283b4 as libc::c_uint,
        0xc5b5eba5 as libc::c_uint,
        0x5ee99583 as libc::c_int as libc::c_uint,
        0x11befd92 as libc::c_int as libc::c_uint,
        0xc04745a1 as libc::c_uint,
        0x8f102db0 as libc::c_uint,
        0x67752870 as libc::c_int as libc::c_uint,
        0x28224061 as libc::c_int as libc::c_uint,
        0xf9dbf852 as libc::c_uint,
        0xb68c9043 as libc::c_uint,
        0xcba219a9 as libc::c_uint,
        0x84f571b8 as libc::c_uint,
        0x550cc98b as libc::c_int as libc::c_uint,
        0x1a5ba19a as libc::c_int as libc::c_uint,
        0xf23ea45a as libc::c_uint,
        0xbd69cc4b as libc::c_uint,
        0x6c907478 as libc::c_int as libc::c_uint,
        0x23c71c69 as libc::c_int as libc::c_uint,
        0xb89b624f as libc::c_uint,
        0xf7cc0a5e as libc::c_uint,
        0x2635b26d as libc::c_int as libc::c_uint,
        0x6962da7c as libc::c_int as libc::c_uint,
        0x8107dfbc as libc::c_uint,
        0xce50b7ad as libc::c_uint,
        0x1fa90f9e as libc::c_int as libc::c_uint,
        0x50fe678f as libc::c_int as libc::c_uint,
        0xe5f41c4a as libc::c_uint,
        0xaaa3745b as libc::c_uint,
        0x7b5acc68 as libc::c_int as libc::c_uint,
        0x340da479 as libc::c_int as libc::c_uint,
        0xdc68a1b9 as libc::c_uint,
        0x933fc9a8 as libc::c_uint,
        0x42c6719b as libc::c_int as libc::c_uint,
        0xd91198a as libc::c_int as libc::c_uint,
        0x96cd67ac as libc::c_uint,
        0xd99a0fbd as libc::c_uint,
        0x863b78e as libc::c_int as libc::c_uint,
        0x4734df9f as libc::c_int as libc::c_uint,
        0xaf51da5f as libc::c_uint,
        0xe006b24e as libc::c_uint,
        0x31ff0a7d as libc::c_int as libc::c_uint,
        0x7ea8626c as libc::c_int as libc::c_uint,
        0x386eb86 as libc::c_int as libc::c_uint,
        0x4cd18397 as libc::c_int as libc::c_uint,
        0x9d283ba4 as libc::c_uint,
        0xd27f53b5 as libc::c_uint,
        0x3a1a5675 as libc::c_int as libc::c_uint,
        0x754d3e64 as libc::c_int as libc::c_uint,
        0xa4b48657 as libc::c_uint,
        0xebe3ee46 as libc::c_uint,
        0x70bf9060 as libc::c_int as libc::c_uint,
        0x3fe8f871 as libc::c_int as libc::c_uint,
        0xee114042 as libc::c_uint,
        0xa1462853 as libc::c_uint,
        0x49232d93 as libc::c_int as libc::c_uint,
        0x6744582 as libc::c_int as libc::c_uint,
        0xd78dfdb1 as libc::c_uint,
        0x98da95a0 as libc::c_uint,
        0xb958178c as libc::c_uint,
        0xf60f7f9d as libc::c_uint,
        0x27f6c7ae as libc::c_int as libc::c_uint,
        0x68a1afbf as libc::c_int as libc::c_uint,
        0x80c4aa7f as libc::c_uint,
        0xcf93c26e as libc::c_uint,
        0x1e6a7a5d as libc::c_int as libc::c_uint,
        0x513d124c as libc::c_int as libc::c_uint,
        0xca616c6a as libc::c_uint,
        0x8536047b as libc::c_uint,
        0x54cfbc48 as libc::c_int as libc::c_uint,
        0x1b98d459 as libc::c_int as libc::c_uint,
        0xf3fdd199 as libc::c_uint,
        0xbcaab988 as libc::c_uint,
        0x6d5301bb as libc::c_int as libc::c_uint,
        0x220469aa as libc::c_int as libc::c_uint,
        0x5f2ae040 as libc::c_int as libc::c_uint,
        0x107d8851 as libc::c_int as libc::c_uint,
        0xc1843062 as libc::c_uint,
        0x8ed35873 as libc::c_uint,
        0x66b65db3 as libc::c_int as libc::c_uint,
        0x29e135a2 as libc::c_int as libc::c_uint,
        0xf8188d91 as libc::c_uint,
        0xb74fe580 as libc::c_uint,
        0x2c139ba6 as libc::c_int as libc::c_uint,
        0x6344f3b7 as libc::c_int as libc::c_uint,
        0xb2bd4b84 as libc::c_uint,
        0xfdea2395 as libc::c_uint,
        0x158f2655 as libc::c_int as libc::c_uint,
        0x5ad84e44 as libc::c_int as libc::c_uint,
        0x8b21f677 as libc::c_uint,
        0xc4769e66 as libc::c_uint,
        0x717ce5a3 as libc::c_int as libc::c_uint,
        0x3e2b8db2 as libc::c_int as libc::c_uint,
        0xefd23581 as libc::c_uint,
        0xa0855d90 as libc::c_uint,
        0x48e05850 as libc::c_int as libc::c_uint,
        0x7b73041 as libc::c_int as libc::c_uint,
        0xd64e8872 as libc::c_uint,
        0x9919e063 as libc::c_uint,
        0x2459e45 as libc::c_int as libc::c_uint,
        0x4d12f654 as libc::c_int as libc::c_uint,
        0x9ceb4e67 as libc::c_uint,
        0xd3bc2676 as libc::c_uint,
        0x3bd923b6 as libc::c_int as libc::c_uint,
        0x748e4ba7 as libc::c_int as libc::c_uint,
        0xa577f394 as libc::c_uint,
        0xea209b85 as libc::c_uint,
        0x970e126f as libc::c_uint,
        0xd8597a7e as libc::c_uint,
        0x9a0c24d as libc::c_int as libc::c_uint,
        0x46f7aa5c as libc::c_int as libc::c_uint,
        0xae92af9c as libc::c_uint,
        0xe1c5c78d as libc::c_uint,
        0x303c7fbe as libc::c_int as libc::c_uint,
        0x7f6b17af as libc::c_int as libc::c_uint,
        0xe4376989 as libc::c_uint,
        0xab600198 as libc::c_uint,
        0x7a99b9ab as libc::c_int as libc::c_uint,
        0x35ced1ba as libc::c_int as libc::c_uint,
        0xddabd47a as libc::c_uint,
        0x92fcbc6b as libc::c_uint,
        0x43050458 as libc::c_int as libc::c_uint,
        0xc526c49 as libc::c_int as libc::c_uint,
    ],
    [
        0 as libc::c_int as libc::c_uint,
        0x5ba1dcca as libc::c_int as libc::c_uint,
        0xb743b994 as libc::c_uint,
        0xece2655e as libc::c_uint,
        0x6a466e9f as libc::c_int as libc::c_uint,
        0x31e7b255 as libc::c_int as libc::c_uint,
        0xdd05d70b as libc::c_uint,
        0x86a40bc1 as libc::c_uint,
        0xd48cdd3e as libc::c_uint,
        0x8f2d01f4 as libc::c_uint,
        0x63cf64aa as libc::c_int as libc::c_uint,
        0x386eb860 as libc::c_int as libc::c_uint,
        0xbecab3a1 as libc::c_uint,
        0xe56b6f6b as libc::c_uint,
        0x9890a35 as libc::c_int as libc::c_uint,
        0x5228d6ff as libc::c_int as libc::c_uint,
        0xadd8a7cb as libc::c_uint,
        0xf6797b01 as libc::c_uint,
        0x1a9b1e5f as libc::c_int as libc::c_uint,
        0x413ac295 as libc::c_int as libc::c_uint,
        0xc79ec954 as libc::c_uint,
        0x9c3f159e as libc::c_uint,
        0x70dd70c0 as libc::c_int as libc::c_uint,
        0x2b7cac0a as libc::c_int as libc::c_uint,
        0x79547af5 as libc::c_int as libc::c_uint,
        0x22f5a63f as libc::c_int as libc::c_uint,
        0xce17c361 as libc::c_uint,
        0x95b61fab as libc::c_uint,
        0x1312146a as libc::c_int as libc::c_uint,
        0x48b3c8a0 as libc::c_int as libc::c_uint,
        0xa451adfe as libc::c_uint,
        0xfff07134 as libc::c_uint,
        0x5f705221 as libc::c_int as libc::c_uint,
        0x4d18eeb as libc::c_int as libc::c_uint,
        0xe833ebb5 as libc::c_uint,
        0xb392377f as libc::c_uint,
        0x35363cbe as libc::c_int as libc::c_uint,
        0x6e97e074 as libc::c_int as libc::c_uint,
        0x8275852a as libc::c_uint,
        0xd9d459e0 as libc::c_uint,
        0x8bfc8f1f as libc::c_uint,
        0xd05d53d5 as libc::c_uint,
        0x3cbf368b as libc::c_int as libc::c_uint,
        0x671eea41 as libc::c_int as libc::c_uint,
        0xe1bae180 as libc::c_uint,
        0xba1b3d4a as libc::c_uint,
        0x56f95814 as libc::c_int as libc::c_uint,
        0xd5884de as libc::c_int as libc::c_uint,
        0xf2a8f5ea as libc::c_uint,
        0xa9092920 as libc::c_uint,
        0x45eb4c7e as libc::c_int as libc::c_uint,
        0x1e4a90b4 as libc::c_int as libc::c_uint,
        0x98ee9b75 as libc::c_uint,
        0xc34f47bf as libc::c_uint,
        0x2fad22e1 as libc::c_int as libc::c_uint,
        0x740cfe2b as libc::c_int as libc::c_uint,
        0x262428d4 as libc::c_int as libc::c_uint,
        0x7d85f41e as libc::c_int as libc::c_uint,
        0x91679140 as libc::c_uint,
        0xcac64d8a as libc::c_uint,
        0x4c62464b as libc::c_int as libc::c_uint,
        0x17c39a81 as libc::c_int as libc::c_uint,
        0xfb21ffdf as libc::c_uint,
        0xa0802315 as libc::c_uint,
        0xbee0a442 as libc::c_uint,
        0xe5417888 as libc::c_uint,
        0x9a31dd6 as libc::c_int as libc::c_uint,
        0x5202c11c as libc::c_int as libc::c_uint,
        0xd4a6cadd as libc::c_uint,
        0x8f071617 as libc::c_uint,
        0x63e57349 as libc::c_int as libc::c_uint,
        0x3844af83 as libc::c_int as libc::c_uint,
        0x6a6c797c as libc::c_int as libc::c_uint,
        0x31cda5b6 as libc::c_int as libc::c_uint,
        0xdd2fc0e8 as libc::c_uint,
        0x868e1c22 as libc::c_uint,
        0x2a17e3 as libc::c_int as libc::c_uint,
        0x5b8bcb29 as libc::c_int as libc::c_uint,
        0xb769ae77 as libc::c_uint,
        0xecc872bd as libc::c_uint,
        0x13380389 as libc::c_int as libc::c_uint,
        0x4899df43 as libc::c_int as libc::c_uint,
        0xa47bba1d as libc::c_uint,
        0xffda66d7 as libc::c_uint,
        0x797e6d16 as libc::c_int as libc::c_uint,
        0x22dfb1dc as libc::c_int as libc::c_uint,
        0xce3dd482 as libc::c_uint,
        0x959c0848 as libc::c_uint,
        0xc7b4deb7 as libc::c_uint,
        0x9c15027d as libc::c_uint,
        0x70f76723 as libc::c_int as libc::c_uint,
        0x2b56bbe9 as libc::c_int as libc::c_uint,
        0xadf2b028 as libc::c_uint,
        0xf6536ce2 as libc::c_uint,
        0x1ab109bc as libc::c_int as libc::c_uint,
        0x4110d576 as libc::c_int as libc::c_uint,
        0xe190f663 as libc::c_uint,
        0xba312aa9 as libc::c_uint,
        0x56d34ff7 as libc::c_int as libc::c_uint,
        0xd72933d as libc::c_int as libc::c_uint,
        0x8bd698fc as libc::c_uint,
        0xd0774436 as libc::c_uint,
        0x3c952168 as libc::c_int as libc::c_uint,
        0x6734fda2 as libc::c_int as libc::c_uint,
        0x351c2b5d as libc::c_int as libc::c_uint,
        0x6ebdf797 as libc::c_int as libc::c_uint,
        0x825f92c9 as libc::c_uint,
        0xd9fe4e03 as libc::c_uint,
        0x5f5a45c2 as libc::c_int as libc::c_uint,
        0x4fb9908 as libc::c_int as libc::c_uint,
        0xe819fc56 as libc::c_uint,
        0xb3b8209c as libc::c_uint,
        0x4c4851a8 as libc::c_int as libc::c_uint,
        0x17e98d62 as libc::c_int as libc::c_uint,
        0xfb0be83c as libc::c_uint,
        0xa0aa34f6 as libc::c_uint,
        0x260e3f37 as libc::c_int as libc::c_uint,
        0x7dafe3fd as libc::c_int as libc::c_uint,
        0x914d86a3 as libc::c_uint,
        0xcaec5a69 as libc::c_uint,
        0x98c48c96 as libc::c_uint,
        0xc365505c as libc::c_uint,
        0x2f873502 as libc::c_int as libc::c_uint,
        0x7426e9c8 as libc::c_int as libc::c_uint,
        0xf282e209 as libc::c_uint,
        0xa9233ec3 as libc::c_uint,
        0x45c15b9d as libc::c_int as libc::c_uint,
        0x1e608757 as libc::c_int as libc::c_uint,
        0x79005533 as libc::c_int as libc::c_uint,
        0x22a189f9 as libc::c_int as libc::c_uint,
        0xce43eca7 as libc::c_uint,
        0x95e2306d as libc::c_uint,
        0x13463bac as libc::c_int as libc::c_uint,
        0x48e7e766 as libc::c_int as libc::c_uint,
        0xa4058238 as libc::c_uint,
        0xffa45ef2 as libc::c_uint,
        0xad8c880d as libc::c_uint,
        0xf62d54c7 as libc::c_uint,
        0x1acf3199 as libc::c_int as libc::c_uint,
        0x416eed53 as libc::c_int as libc::c_uint,
        0xc7cae692 as libc::c_uint,
        0x9c6b3a58 as libc::c_uint,
        0x70895f06 as libc::c_int as libc::c_uint,
        0x2b2883cc as libc::c_int as libc::c_uint,
        0xd4d8f2f8 as libc::c_uint,
        0x8f792e32 as libc::c_uint,
        0x639b4b6c as libc::c_int as libc::c_uint,
        0x383a97a6 as libc::c_int as libc::c_uint,
        0xbe9e9c67 as libc::c_uint,
        0xe53f40ad as libc::c_uint,
        0x9dd25f3 as libc::c_int as libc::c_uint,
        0x527cf939 as libc::c_int as libc::c_uint,
        0x542fc6 as libc::c_int as libc::c_uint,
        0x5bf5f30c as libc::c_int as libc::c_uint,
        0xb7179652 as libc::c_uint,
        0xecb64a98 as libc::c_uint,
        0x6a124159 as libc::c_int as libc::c_uint,
        0x31b39d93 as libc::c_int as libc::c_uint,
        0xdd51f8cd as libc::c_uint,
        0x86f02407 as libc::c_uint,
        0x26700712 as libc::c_int as libc::c_uint,
        0x7dd1dbd8 as libc::c_int as libc::c_uint,
        0x9133be86 as libc::c_uint,
        0xca92624c as libc::c_uint,
        0x4c36698d as libc::c_int as libc::c_uint,
        0x1797b547 as libc::c_int as libc::c_uint,
        0xfb75d019 as libc::c_uint,
        0xa0d40cd3 as libc::c_uint,
        0xf2fcda2c as libc::c_uint,
        0xa95d06e6 as libc::c_uint,
        0x45bf63b8 as libc::c_int as libc::c_uint,
        0x1e1ebf72 as libc::c_int as libc::c_uint,
        0x98bab4b3 as libc::c_uint,
        0xc31b6879 as libc::c_uint,
        0x2ff90d27 as libc::c_int as libc::c_uint,
        0x7458d1ed as libc::c_int as libc::c_uint,
        0x8ba8a0d9 as libc::c_uint,
        0xd0097c13 as libc::c_uint,
        0x3ceb194d as libc::c_int as libc::c_uint,
        0x674ac587 as libc::c_int as libc::c_uint,
        0xe1eece46 as libc::c_uint,
        0xba4f128c as libc::c_uint,
        0x56ad77d2 as libc::c_int as libc::c_uint,
        0xd0cab18 as libc::c_int as libc::c_uint,
        0x5f247de7 as libc::c_int as libc::c_uint,
        0x485a12d as libc::c_int as libc::c_uint,
        0xe867c473 as libc::c_uint,
        0xb3c618b9 as libc::c_uint,
        0x35621378 as libc::c_int as libc::c_uint,
        0x6ec3cfb2 as libc::c_int as libc::c_uint,
        0x8221aaec as libc::c_uint,
        0xd9807626 as libc::c_uint,
        0xc7e0f171 as libc::c_uint,
        0x9c412dbb as libc::c_uint,
        0x70a348e5 as libc::c_int as libc::c_uint,
        0x2b02942f as libc::c_int as libc::c_uint,
        0xada69fee as libc::c_uint,
        0xf6074324 as libc::c_uint,
        0x1ae5267a as libc::c_int as libc::c_uint,
        0x4144fab0 as libc::c_int as libc::c_uint,
        0x136c2c4f as libc::c_int as libc::c_uint,
        0x48cdf085 as libc::c_int as libc::c_uint,
        0xa42f95db as libc::c_uint,
        0xff8e4911 as libc::c_uint,
        0x792a42d0 as libc::c_int as libc::c_uint,
        0x228b9e1a as libc::c_int as libc::c_uint,
        0xce69fb44 as libc::c_uint,
        0x95c8278e as libc::c_uint,
        0x6a3856ba as libc::c_int as libc::c_uint,
        0x31998a70 as libc::c_int as libc::c_uint,
        0xdd7bef2e as libc::c_uint,
        0x86da33e4 as libc::c_uint,
        0x7e3825 as libc::c_int as libc::c_uint,
        0x5bdfe4ef as libc::c_int as libc::c_uint,
        0xb73d81b1 as libc::c_uint,
        0xec9c5d7b as libc::c_uint,
        0xbeb48b84 as libc::c_uint,
        0xe515574e as libc::c_uint,
        0x9f73210 as libc::c_int as libc::c_uint,
        0x5256eeda as libc::c_int as libc::c_uint,
        0xd4f2e51b as libc::c_uint,
        0x8f5339d1 as libc::c_uint,
        0x63b15c8f as libc::c_int as libc::c_uint,
        0x38108045 as libc::c_int as libc::c_uint,
        0x9890a350 as libc::c_uint,
        0xc3317f9a as libc::c_uint,
        0x2fd31ac4 as libc::c_int as libc::c_uint,
        0x7472c60e as libc::c_int as libc::c_uint,
        0xf2d6cdcf as libc::c_uint,
        0xa9771105 as libc::c_uint,
        0x4595745b as libc::c_int as libc::c_uint,
        0x1e34a891 as libc::c_int as libc::c_uint,
        0x4c1c7e6e as libc::c_int as libc::c_uint,
        0x17bda2a4 as libc::c_int as libc::c_uint,
        0xfb5fc7fa as libc::c_uint,
        0xa0fe1b30 as libc::c_uint,
        0x265a10f1 as libc::c_int as libc::c_uint,
        0x7dfbcc3b as libc::c_int as libc::c_uint,
        0x9119a965 as libc::c_uint,
        0xcab875af as libc::c_uint,
        0x3548049b as libc::c_int as libc::c_uint,
        0x6ee9d851 as libc::c_int as libc::c_uint,
        0x820bbd0f as libc::c_uint,
        0xd9aa61c5 as libc::c_uint,
        0x5f0e6a04 as libc::c_int as libc::c_uint,
        0x4afb6ce as libc::c_int as libc::c_uint,
        0xe84dd390 as libc::c_uint,
        0xb3ec0f5a as libc::c_uint,
        0xe1c4d9a5 as libc::c_uint,
        0xba65056f as libc::c_uint,
        0x56876031 as libc::c_int as libc::c_uint,
        0xd26bcfb as libc::c_int as libc::c_uint,
        0x8b82b73a as libc::c_uint,
        0xd0236bf0 as libc::c_uint,
        0x3cc10eae as libc::c_int as libc::c_uint,
        0x6760d264 as libc::c_int as libc::c_uint,
    ],
];
pub unsafe fn ogg_page_version(og: *const ogg_page) -> i32 {
    if og.is_null() {
        return 0;
    }
    let header = (*og).header;
    if header.is_null() {
        return 0;
    }
    *header.offset(4) as i32
}
pub unsafe fn ogg_page_continued(og: *const ogg_page) -> i32 {
    if og.is_null() {
        return 0;
    }
    let header = (*og).header;
    if header.is_null() {
        return 0;
    }
    (*header.offset(5) & 0x01) as i32
}
pub unsafe fn ogg_page_bos(og: *const ogg_page) -> libc::c_int {
    if og.is_null() {
        return 0;
    }
    let header = (*og).header;
    if header.is_null() {
        return 0;
    }
    (*header.offset(5) & 0x02) as libc::c_int
}
pub unsafe fn ogg_page_eos(og: *const ogg_page) -> libc::c_int {
    if og.is_null() {
        return 0;
    }
    let header = (*og).header;
    if header.is_null() {
        return 0;
    }
    (*header.offset(5) & 0x04) as libc::c_int
}
pub unsafe fn ogg_page_granulepos(og: *const ogg_page) -> libc::c_long {
    let page = (*og).header;
    let mut granulepos: u64 = *page.add(13) as u64;
    granulepos = (granulepos << 8) | (*page.add(12) as u64);
    granulepos = (granulepos << 8) | (*page.add(11) as u64);
    granulepos = (granulepos << 8) | (*page.add(10) as u64);
    granulepos = (granulepos << 8) | (*page.add(9) as u64);
    granulepos = (granulepos << 8) | (*page.add(8) as u64);
    granulepos = (granulepos << 8) | (*page.add(7) as u64);
    granulepos = (granulepos << 8) | (*page.add(6) as u64);
    granulepos as libc::c_long
}
pub unsafe fn ogg_page_serialno(og: *const ogg_page) -> i32 {
    let header = (*og).header;
    ((*header.offset(14) as u32)
        | ((*header.offset(15) as u32) << 8)
        | ((*header.offset(16) as u32) << 16)
        | ((*header.offset(17) as u32) << 24)) as i32
}
pub unsafe fn ogg_page_pageno(og: *const ogg_page) -> libc::c_long {
    let header = (*og).header;
    let pageno = (*header.offset(18) as libc::c_uint)
        | ((*header.offset(19) as libc::c_uint) << 8)
        | ((*header.offset(20) as libc::c_uint) << 16)
        | ((*header.offset(21) as libc::c_uint) << 24);
    pageno as libc::c_long
}
pub unsafe fn ogg_page_packets(og: *const ogg_page) -> i32 {
    let n = *(*og).header.offset(26) as i32;
    let mut count = 0;
    for i in 0..n {
        if *(*og).header.offset(27 + i as isize) < 255 {
            count += 1;
        }
    }
    count
}
pub unsafe fn ogg_stream_init(os: *mut ogg_stream_state, serialno: c_int) -> c_int {
    if !os.is_null() {
        memset(
            os as *mut libc::c_void,
            0,
            std::mem::size_of::<ogg_stream_state>() as size_t,
        );
        (*os).body_storage = 16 * 1024;
        (*os).lacing_storage = 1024;
        (*os).body_data =
            malloc((*os).body_storage as size_t * std::mem::size_of::<c_uchar>()) as *mut c_uchar;
        (*os).lacing_vals =
            malloc((*os).lacing_storage as size_t * std::mem::size_of::<c_int>()) as *mut c_int;
        (*os).granule_vals =
            malloc((*os).lacing_storage as size_t * std::mem::size_of::<c_long>()) as *mut c_long;
        if (*os).body_data.is_null() || (*os).lacing_vals.is_null() || (*os).granule_vals.is_null()
        {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).serialno = serialno as c_long;
        return 0;
    }
    -1
}
pub unsafe fn ogg_stream_check(os: *mut ogg_stream_state) -> libc::c_int {
    if os.is_null() || (*os).body_data.is_null() {
        return -1;
    }
    0
}
pub unsafe fn ogg_stream_clear(os: *mut ogg_stream_state) -> c_int {
    if !os.is_null() {
        if !(*os).body_data.is_null() {
            free((*os).body_data as *mut libc::c_void);
        }
        if !(*os).lacing_vals.is_null() {
            free((*os).lacing_vals as *mut libc::c_void);
        }
        if !(*os).granule_vals.is_null() {
            free((*os).granule_vals as *mut libc::c_void);
        }
        memset(
            os as *mut libc::c_void,
            0,
            std::mem::size_of::<ogg_stream_state>(),
        );
    }
    0
}
pub unsafe fn ogg_stream_destroy(os: *mut ogg_stream_state) -> c_int {
    if !os.is_null() {
        ogg_stream_clear(os);
        free(os as *mut libc::c_void);
    }
    0
}
pub unsafe fn _os_body_expand(os: *mut ogg_stream_state, needed: libc::c_long) -> libc::c_int {
    const LONG_MAX: libc::c_long = libc::c_long::MAX;
    if (*os).body_storage - needed <= (*os).body_fill {
        let mut body_storage: libc::c_long;
        
        if (*os).body_storage > LONG_MAX - needed {
            ogg_stream_clear(os);
            return -1;
        }
        body_storage = (*os).body_storage + needed;
        if body_storage < LONG_MAX - 1024 {
            body_storage += 1024;
        }
        let ret: *mut libc::c_void = libc::realloc(
            (*os).body_data as *mut libc::c_void,
            (body_storage as usize) * std::mem::size_of::<libc::c_uchar>(),
        );
        if ret.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).body_storage = body_storage;
        (*os).body_data = ret as *mut libc::c_uchar;
    }
    0
}
pub unsafe fn _os_lacing_expand(os: *mut ogg_stream_state, needed: c_long) -> c_int {
    if (*os).lacing_storage - needed <= (*os).lacing_fill {
        let mut lacing_storage: c_long;
        let mut ret: *mut libc::c_void;
        if (*os).lacing_storage > i64::MAX - needed {
            ogg_stream_clear(os);
            return -1;
        }
        lacing_storage = (*os).lacing_storage + needed;
        if lacing_storage < i64::MAX - 32 {
            lacing_storage += 32;
        }
        ret = realloc(
            (*os).lacing_vals as *mut libc::c_void,
            lacing_storage as usize * std::mem::size_of::<libc::c_int>(),
        );
        if ret.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).lacing_vals = ret as *mut libc::c_int;
        ret = realloc(
            (*os).granule_vals as *mut libc::c_void,
            lacing_storage as usize * std::mem::size_of::<libc::c_long>(),
        );
        if ret.is_null() {
            ogg_stream_clear(os);
            return -1;
        }
        (*os).granule_vals = ret as *mut libc::c_long;
        (*os).lacing_storage = lacing_storage;
    }
    0
}
pub unsafe fn _os_update_crc(
    mut crc: libc::c_uint,
    mut buffer: *mut libc::c_uchar,
    mut size: libc::c_int,
) -> libc::c_uint {
    while size >= 8 {
        crc ^= ((*buffer.offset(0) as libc::c_uint) << 24)
            | ((*buffer.offset(1) as libc::c_uint) << 16)
            | ((*buffer.offset(2) as libc::c_uint) << 8)
            | (*buffer.offset(3) as libc::c_uint);
        crc = crc_lookup[7][(crc >> 24) as usize]
            ^ crc_lookup[6][((crc >> 16) & 0xFF) as usize]
            ^ crc_lookup[5][((crc >> 8) & 0xFF) as usize]
            ^ crc_lookup[4][(crc & 0xFF) as usize]
            ^ crc_lookup[3][*buffer.offset(4) as usize]
            ^ crc_lookup[2][*buffer.offset(5) as usize]
            ^ crc_lookup[1][*buffer.offset(6) as usize]
            ^ crc_lookup[0][*buffer.offset(7) as usize];
        buffer = buffer.offset(8);
        size -= 8;
    }
    while size > 0 {
        crc =
            (crc << 8) ^ crc_lookup[0][(((crc >> 24) & 0xFF) ^ (*buffer as libc::c_uint)) as usize];
        buffer = buffer.offset(1);
        size -= 1;
    }
    crc
}
pub unsafe fn ogg_page_checksum_set(og: *mut ogg_page) {
    if !og.is_null() {
        let mut crc_reg: libc::c_uint = 0;
        let og = &mut *og;
        (*og.header.offset(22)) = 0;
        (*og.header.offset(23)) = 0;
        (*og.header.offset(24)) = 0;
        (*og.header.offset(25)) = 0;
        crc_reg = _os_update_crc(crc_reg, og.header, og.header_len as libc::c_int);
        crc_reg = _os_update_crc(crc_reg, og.body, og.body_len as libc::c_int);
        (*og.header.offset(22)) = (crc_reg & 0xff) as libc::c_uchar;
        (*og.header.offset(23)) = ((crc_reg >> 8) & 0xff) as libc::c_uchar;
        (*og.header.offset(24)) = ((crc_reg >> 16) & 0xff) as libc::c_uchar;
        (*og.header.offset(25)) = ((crc_reg >> 24) & 0xff) as libc::c_uchar;
    }
}
pub unsafe fn ogg_stream_iovecin(
    os: *mut ogg_stream_state,
    iov: *mut ogg_iovec_t,
    count: c_int,
    e_o_s: c_long,
    granulepos: c_long,
) -> c_int {
    let mut bytes: c_long = 0;
    let lacing_vals: c_long;
    let mut i: c_int;
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    if iov.is_null() {
        return 0;
    }
    for i in 0..count {
        let iov_len = (*iov.add(i as usize)).iov_len;
        if iov_len > std::i64::MAX as size_t {
            return -1;
        }
        if bytes > std::i64::MAX - iov_len as c_long {
            return -1;
        }
        bytes += iov_len as c_long;
    }
    lacing_vals = bytes / 255 + 1;
    if (*os).body_returned != 0 {
        (*os).body_fill -= (*os).body_returned;
        if (*os).body_fill != 0 {
            memmove(
                (*os).body_data as *mut c_void,
                (*os).body_data.add((*os).body_returned as usize) as *const c_void,
                (*os).body_fill as usize,
            );
        }
        (*os).body_returned = 0;
    }
    if _os_body_expand(os, bytes) != 0 || _os_lacing_expand(os, lacing_vals) != 0 {
        return -1;
    }
    for i in 0..count {
        let iov_base = (*iov.add(i as usize)).iov_base;
        let iov_len = (*iov.add(i as usize)).iov_len;
        memcpy(
            (*os).body_data.add((*os).body_fill as usize) as *mut c_void,
            iov_base,
            iov_len,
        );
        (*os).body_fill += iov_len as c_long;
    }
    for i in 0..lacing_vals - 1 {
        *(*os)
            .lacing_vals
            .add((*os).lacing_fill as usize + i as usize) = 255;
        *(*os)
            .granule_vals
            .add((*os).lacing_fill as usize + i as usize) = (*os).granulepos;
    }
    *(*os)
        .lacing_vals
        .add((*os).lacing_fill as usize + (lacing_vals - 1) as usize) = (bytes % 255) as c_int;
    (*os).granulepos = granulepos;
    *(*os)
        .granule_vals
        .add((*os).lacing_fill as usize + (lacing_vals - 1) as usize) = granulepos;
    *(*os).lacing_vals.add((*os).lacing_fill as usize) |= 0x100;
    (*os).lacing_fill += lacing_vals;
    (*os).packetno += 1;
    if e_o_s != 0 {
        (*os).e_o_s = 1;
    }
    0
}
pub unsafe fn ogg_stream_packetin(os: *mut ogg_stream_state, op: *mut ogg_packet) -> c_int {
    let mut iov = ogg_iovec_t {
        iov_base: (*op).packet as *mut c_void,
        iov_len: (*op).bytes as size_t,
    };
    ogg_stream_iovecin(os, &mut iov, 1, (*op).e_o_s, (*op).granulepos)
}
pub unsafe fn ogg_stream_flush_i(
    os: *mut ogg_stream_state,
    og: *mut ogg_page,
    mut force: libc::c_int,
    nfill: libc::c_int,
) -> libc::c_int {
    let mut vals: libc::c_int = 0;
    
    let mut bytes: libc::c_int = 0;
    let mut acc: libc::c_long = 0;
    let mut granule_pos: libc::c_long = -1;
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    let maxvals: libc::c_int = if (*os).lacing_fill > 255 {
        255
    } else {
        (*os).lacing_fill as libc::c_int
    };
    if maxvals == 0 {
        return 0;
    }
    if (*os).b_o_s == 0 {
        granule_pos = 0;
        for v in 0..maxvals {
            if (*(*os).lacing_vals.offset(v as isize) & 0x0ff) < 255 {
                vals = v + 1;
                break;
            }
        }
    } else {
        let mut packets_done: libc::c_int = 0;
        let mut packet_just_done: libc::c_int = 0;
        for v in 0..maxvals {
            if acc > nfill as libc::c_long && packet_just_done >= 4 {
                force = 1;
                break;
            }
            acc += (*(*os).lacing_vals.offset(v as isize) & 0x0ff) as libc::c_long;
            if (*(*os).lacing_vals.offset(v as isize) & 0xff) < 255 {
                granule_pos = *(*os).granule_vals.offset(v as isize);
                packet_just_done = packets_done + 1;
                packets_done = packet_just_done;
            } else {
                packet_just_done = 0;
            }
            vals = v + 1;
        }
        if vals == 255 {
            force = 1;
        }
    }
    if force == 0 {
        return 0;
    }
    libc::memcpy(
        (*os).header.as_mut_ptr() as *mut libc::c_void,
        b"OggS\0".as_ptr() as *const libc::c_void,
        4,
    );
    (*os).header[4] = 0x00;
    (*os).header[5] = 0x00;
    if (*(*os).lacing_vals.offset(0) & 0x100) == 0 {
        (*os).header[5] |= 0x01;
    }
    if (*os).b_o_s == 0 {
        (*os).header[5] |= 0x02;
    }
    if (*os).e_o_s != 0 && (*os).lacing_fill == vals as libc::c_long {
        (*os).header[5] |= 0x04;
    }
    (*os).b_o_s = 1;
    for i in 6..14 {
        (*os).header[i] = (granule_pos & 0xff) as libc::c_uchar;
        granule_pos >>= 8;
    }
    let mut serialno = (*os).serialno;
    for i in 14..18 {
        (*os).header[i] = (serialno & 0xff) as libc::c_uchar;
        serialno >>= 8;
    }
    if (*os).pageno == -1 {
        (*os).pageno = 0;
    }
    let mut pageno = (*os).pageno;
    (*os).pageno += 1;
    for i in 18..22 {
        (*os).header[i] = (pageno & 0xff) as libc::c_uchar;
        pageno >>= 8;
    }
    (*os).header[22] = 0;
    (*os).header[23] = 0;
    (*os).header[24] = 0;
    (*os).header[25] = 0;
    (*os).header[26] = (vals & 0xff) as libc::c_uchar;
    for i in 0..vals {
        bytes += {
            let val = (*(*os).lacing_vals.offset(i as isize) & 0xff) as libc::c_uchar;
            (*os).header[i as usize + 27] = val;
            val as libc::c_int
        };
    }
    (*og).header = (*os).header.as_mut_ptr();
    (*og).header_len = (vals + 27) as libc::c_long;
    (*os).header_fill = (vals + 27) as libc::c_int;
    (*og).body = (*os).body_data.offset((*os).body_returned as isize);
    (*og).body_len = bytes as libc::c_long;
    (*os).lacing_fill -= vals as libc::c_long;
    libc::memmove(
        (*os).lacing_vals as *mut libc::c_void,
        (*os).lacing_vals.offset(vals as isize) as *const libc::c_void,
        ((*os).lacing_fill as usize) * std::mem::size_of::<libc::c_int>(),
    );
    libc::memmove(
        (*os).granule_vals as *mut libc::c_void,
        (*os).granule_vals.offset(vals as isize) as *const libc::c_void,
        ((*os).lacing_fill as usize) * std::mem::size_of::<libc::c_long>(),
    );
    (*os).body_returned += bytes as libc::c_long;
    ogg_page_checksum_set(og);
    1
}
pub unsafe fn ogg_stream_flush(os: *mut ogg_stream_state, og: *mut ogg_page) -> libc::c_int {
    ogg_stream_flush_i(os, og, 1, 4096)
}
pub unsafe fn ogg_stream_flush_fill(
    os: *mut ogg_stream_state,
    og: *mut ogg_page,
    nfill: libc::c_int,
) -> libc::c_int {
    ogg_stream_flush_i(os, og, 1, nfill)
}
pub unsafe fn ogg_stream_pageout(os: *mut ogg_stream_state, og: *mut ogg_page) -> libc::c_int {
    let mut force = 0;
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    if ((*os).e_o_s != 0 && (*os).lacing_fill != 0) || ((*os).lacing_fill != 0 && (*os).b_o_s == 0)
    {
        force = 1;
    }
    ogg_stream_flush_i(os, og, force, 4096)
}
pub unsafe fn ogg_stream_pageout_fill(
    os: *mut ogg_stream_state,
    og: *mut ogg_page,
    nfill: libc::c_int,
) -> libc::c_int {
    let mut force = 0;
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    if ((*os).e_o_s != 0 && (*os).lacing_fill != 0) || ((*os).lacing_fill != 0 && (*os).b_o_s == 0)
    {
        force = 1;
    }
    ogg_stream_flush_i(os, og, force, nfill)
}
pub unsafe fn ogg_stream_eos(os: *mut ogg_stream_state) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return 1;
    }
    (*os).e_o_s
}
pub unsafe fn ogg_sync_init(oy: *mut ogg_sync_state) -> c_int {
    if !oy.is_null() {
        (*oy).storage = -1;
        memset(
            oy as *mut libc::c_void,
            0,
            std::mem::size_of::<ogg_sync_state>(),
        );
    }
    0
}
pub unsafe fn ogg_sync_clear(oy: *mut ogg_sync_state) -> c_int {
    if !oy.is_null() {
        if !(*oy).data.is_null() {
            free((*oy).data as *mut c_void);
        }
        memset(oy as *mut c_void, 0, std::mem::size_of::<ogg_sync_state>());
    }
    0
}
pub unsafe fn ogg_sync_destroy(oy: *mut ogg_sync_state) -> c_int {
    if !oy.is_null() {
        ogg_sync_clear(oy);
        free(oy as *mut libc::c_void);
    }
    0
}
pub unsafe fn ogg_sync_check(oy: *mut ogg_sync_state) -> libc::c_int {
    if (*oy).storage < 0 {
        return -1;
    }
    0
}
pub unsafe fn ogg_sync_buffer(oy: *mut ogg_sync_state, size: c_long) -> *mut c_char {
    if ogg_sync_check(oy) != 0 {
        return std::ptr::null_mut();
    }
    if (*oy).returned != 0 {
        (*oy).fill -= (*oy).returned;
        if (*oy).fill > 0 {
            memmove(
                (*oy).data as *mut c_void,
                (*oy).data.add((*oy).returned as usize) as *const c_void,
                (*oy).fill as usize,
            );
        }
        (*oy).returned = 0;
    }
    if size > (*oy).storage as c_long - (*oy).fill as c_long {
        let newsize: c_long;
        let ret: *mut c_void;
        if size > (INT_MAX - 4096 - (*oy).fill) as c_long {
            ogg_sync_clear(oy);
            return std::ptr::null_mut();
        }
        newsize = size + (*oy).fill as c_long + 4096;
        if !(*oy).data.is_null() {
            ret = realloc((*oy).data as *mut c_void, newsize as usize);
        } else {
            ret = malloc(newsize as usize);
        }
        if ret.is_null() {
            ogg_sync_clear(oy);
            return std::ptr::null_mut();
        }
        (*oy).data = ret as *mut libc::c_uchar;
        (*oy).storage = newsize as c_int;
    }
    (*oy).data.add((*oy).fill as usize) as *mut c_char
}
pub unsafe fn ogg_sync_wrote(oy: *mut ogg_sync_state, bytes: libc::c_long) -> libc::c_int {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    if (*oy).fill + bytes as libc::c_int > (*oy).storage {
        return -1;
    }
    (*oy).fill += bytes as libc::c_int;
    0
}
pub unsafe fn ogg_sync_pageseek(oy: *mut ogg_sync_state, og: *mut ogg_page) -> libc::c_long {
    
    let mut next: *mut libc::c_uchar = std::ptr::null_mut();
    let mut bytes: libc::c_long;
    if ogg_sync_check(oy) != 0 {
        return 0;
    }
    let page: *mut libc::c_uchar = (*oy).data.offset((*oy).returned as isize);
    bytes = (*oy).fill as libc::c_long - (*oy).returned as libc::c_long;
    if (*oy).headerbytes == 0 {
        
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
        let headerbytes: libc::c_int = *page.offset(26) as libc::c_int + 27;
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
        bytes
    }
}
pub unsafe fn ogg_sync_pageout(oy: *mut ogg_sync_state, og: *mut ogg_page) -> libc::c_int {
    if ogg_sync_check(oy) != 0 {
        return 0;
    }
    loop {
        let ret = ogg_sync_pageseek(oy, og);
        if ret > 0 {
            return 1;
        }
        if ret == 0 {
            return 0;
        }
        if (*oy).unsynced == 0 {
            (*oy).unsynced = 1;
            return -1;
        }
    }
}
pub unsafe fn ogg_stream_pagein(os: *mut ogg_stream_state, og: *mut ogg_page) -> c_int {
    let header = (*og).header;
    let mut body = (*og).body;
    let mut bodysize = (*og).body_len;
    let mut segptr = 0;
    let version = ogg_page_version(og);
    let continued = ogg_page_continued(og);
    let mut bos = ogg_page_bos(og);
    let eos = ogg_page_eos(og);
    let granulepos = ogg_page_granulepos(og);
    let serialno = ogg_page_serialno(og);
    let pageno = ogg_page_pageno(og);
    let segments = *header.offset(26) as c_int;
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    {
        let lr = (*os).lacing_returned;
        let br = (*os).body_returned;
        if br != 0 {
            (*os).body_fill -= br;
            if (*os).body_fill != 0 {
                memmove(
                    (*os).body_data as *mut libc::c_void,
                    (*os).body_data.offset(br as isize) as *const libc::c_void,
                    (*os).body_fill as usize,
                );
            }
            (*os).body_returned = 0;
        }
        if lr != 0 {
            if (*os).lacing_fill - lr != 0 {
                memmove(
                    (*os).lacing_vals as *mut libc::c_void,
                    (*os).lacing_vals.offset(lr as isize) as *const libc::c_void,
                    ((*os).lacing_fill - lr) as usize * std::mem::size_of::<c_int>(),
                );
                memmove(
                    (*os).granule_vals as *mut libc::c_void,
                    (*os).granule_vals.offset(lr as isize) as *const libc::c_void,
                    ((*os).lacing_fill - lr) as usize * std::mem::size_of::<c_long>(),
                );
            }
            (*os).lacing_fill -= lr;
            (*os).lacing_packet -= lr;
            (*os).lacing_returned = 0;
        }
    }
    if serialno != (*os).serialno as i32 {
        return -1;
    }
    if version > 0 {
        return -1;
    }
    if _os_lacing_expand(os, segments as c_long + 1) != 0 {
        return -1;
    }
    if pageno != (*os).pageno {
        for i in (*os).lacing_packet..(*os).lacing_fill {
            (*os).body_fill -= (*(*os).lacing_vals.offset(i as isize) & 0xff) as c_long;
        }
        (*os).lacing_fill = (*os).lacing_packet;
        if (*os).pageno != -1 {
            *(*os).lacing_vals.offset((*os).lacing_fill as isize) = 0x400;
            (*os).lacing_fill += 1;
            (*os).lacing_packet += 1;
        }
    }
    if continued != 0
        && ((*os).lacing_fill < 1
            || (*(*os).lacing_vals.offset((*os).lacing_fill as isize - 1) & 0xff) < 255
            || *(*os).lacing_vals.offset((*os).lacing_fill as isize - 1) == 0x400)
        {
            bos = 0;
            while segptr < segments {
                let val = *header.offset(27 + segptr as isize) as c_int;
                body = body.offset(val as isize);
                bodysize -= val as c_long;
                if val < 255 {
                    segptr += 1;
                    break;
                }
                segptr += 1;
            }
        }
    if bodysize != 0 {
        if _os_body_expand(os, bodysize) != 0 {
            return -1;
        }
        memcpy(
            (*os).body_data.offset((*os).body_fill as isize) as *mut libc::c_void,
            body as *const libc::c_void,
            bodysize as usize,
        );
        (*os).body_fill += bodysize;
    }
    {
        let mut saved = -1;
        while segptr < segments {
            let val = *header.offset(27 + segptr as isize) as c_int;
            *(*os).lacing_vals.offset((*os).lacing_fill as isize) = val;
            *(*os).granule_vals.offset((*os).lacing_fill as isize) = -1;
            if bos != 0 {
                *(*os).lacing_vals.offset((*os).lacing_fill as isize) |= 0x100;
                bos = 0;
            }
            if val < 255 {
                saved = (*os).lacing_fill;
            }
            (*os).lacing_fill += 1;
            segptr += 1;
            if val < 255 {
                (*os).lacing_packet = (*os).lacing_fill;
            }
        }
        if saved != -1 {
            *(*os).granule_vals.offset(saved as isize) = granulepos;
        }
    }
    if eos != 0 {
        (*os).e_o_s = 1;
        if (*os).lacing_fill > 0 {
            *(*os).lacing_vals.offset((*os).lacing_fill as isize - 1) |= 0x200;
        }
    }
    (*os).pageno = pageno + 1;
    0
}
pub unsafe fn ogg_sync_reset(oy: *mut ogg_sync_state) -> libc::c_int {
    if ogg_sync_check(oy) != 0 {
        return -1;
    }
    (*oy).fill = 0;
    (*oy).returned = 0;
    (*oy).unsynced = 0;
    (*oy).headerbytes = 0;
    (*oy).bodybytes = 0;
    0
}
pub unsafe fn ogg_stream_reset(os: *mut ogg_stream_state) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    (*os).body_fill = 0;
    (*os).body_returned = 0;
    (*os).lacing_fill = 0;
    (*os).lacing_packet = 0;
    (*os).lacing_returned = 0;
    (*os).header_fill = 0;
    (*os).e_o_s = 0;
    (*os).b_o_s = 0;
    (*os).pageno = -1;
    (*os).packetno = 0;
    (*os).granulepos = 0;
    0
}
pub unsafe fn ogg_stream_reset_serialno(
    os: *mut ogg_stream_state,
    serialno: libc::c_int,
) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return -1;
    }
    ogg_stream_reset(os);
    (*os).serialno = serialno as libc::c_long;
    0
}
pub unsafe fn _packetout(
    os: *mut ogg_stream_state,
    op: *mut ogg_packet,
    adv: libc::c_int,
) -> libc::c_int {
    let mut ptr = (*os).lacing_returned;
    if (*os).lacing_packet <= ptr {
        return 0;
    }
    if *(*os).lacing_vals.offset(ptr as isize) & 0x400 != 0 {
        (*os).lacing_returned += 1;
        (*os).packetno += 1;
        return -1;
    }
    if op.is_null() && adv == 0 {
        return 1;
    }
    let mut size = *(*os).lacing_vals.offset(ptr as isize) & 0xff;
    let mut bytes = size as libc::c_long;
    let mut eos = *(*os).lacing_vals.offset(ptr as isize) & 0x200;
    let bos = *(*os).lacing_vals.offset(ptr as isize) & 0x100;
    while size == 255 {
        ptr += 1;
        let val = *(*os).lacing_vals.offset(ptr as isize);
        size = val & 0xff;
        if val & 0x200 != 0 {
            eos = 0x200;
        }
        bytes += size as libc::c_long;
    }
    if !op.is_null() {
        (*op).e_o_s = eos as libc::c_long;
        (*op).b_o_s = bos as libc::c_long;
        (*op).packet = (*os).body_data.offset((*os).body_returned as isize);
        (*op).packetno = (*os).packetno;
        (*op).granulepos = *(*os).granule_vals.offset(ptr as isize);
        (*op).bytes = bytes;
    }
    if adv != 0 {
        (*os).body_returned += bytes;
        (*os).lacing_returned = ptr + 1;
        (*os).packetno += 1;
    }
    1
}
pub unsafe fn ogg_stream_packetout(os: *mut ogg_stream_state, op: *mut ogg_packet) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    _packetout(os, op, 1)
}
pub unsafe fn ogg_stream_packetpeek(os: *mut ogg_stream_state, op: *mut ogg_packet) -> libc::c_int {
    if ogg_stream_check(os) != 0 {
        return 0;
    }
    _packetout(os, op, 0)
}
pub unsafe fn ogg_packet_clear(op: *mut ogg_packet) {
    if !(*op).packet.is_null() {
        free((*op).packet as *mut c_void);
    }
    memset(op as *mut c_void, 0, std::mem::size_of::<ogg_packet>());
}
