/* Source file for generating test .o file for Sactor translation.
 * How this file is made:
 * Copy src/framing.c ;
 * Delete all function definitions outside of `#ifdef *TEST` ... `#endif` block;
 * Delete `#ifdef *TEST` and its corresponding `#endif`.
 * 
 * Compile this into .o file: ```bash
 * cd [path/to/ogg]/src
 * # check your `make` output for whether to include `-DHAVE_CONFIG_H` below
 * gcc -DHAVE_CONFIG_H -I. -I..  -I../include -I../include  -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -O2 -c -o ../../test_framing.o ../../test_framing.c -Og -g
 * ```
*/


/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE Ogg CONTAINER SOURCE CODE.              *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2018             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: code raw packets into framed OggSquish stream and
           decode Ogg streams back into raw packets

 note: The CRC code is directly derived from public domain code by
 Ross Williams (ross@guest.adelaide.edu.au).  See docs/framing.html
 for details.

 ********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ogg/ogg.h>

#include <stdio.h>

ogg_stream_state os_en, os_de;
ogg_sync_state oy;

void checkpacket(ogg_packet *op,long len, int no, long pos){
  long j;
  static int sequence=0;
  static int lastno=0;

  if(op->bytes!=len){
    fprintf(stderr,"incorrect packet length (%ld != %ld)!\n",op->bytes,len);
    exit(1);
  }
  if(op->granulepos!=pos){
    fprintf(stderr,"incorrect packet granpos (%ld != %ld)!\n",(long)op->granulepos,pos);
    exit(1);
  }

  /* packet number just follows sequence/gap; adjust the input number
     for that */
  if(no==0){
    sequence=0;
  }else{
    sequence++;
    if(no>lastno+1)
      sequence++;
  }
  lastno=no;
  if(op->packetno!=sequence){
    fprintf(stderr,"incorrect packet sequence %ld != %d\n",
            (long)(op->packetno),sequence);
    exit(1);
  }

  /* Test data */
  for(j=0;j<op->bytes;j++)
    if(op->packet[j]!=((j+no)&0xff)){
      fprintf(stderr,"body data mismatch (1) at pos %ld: %x!=%lx!\n\n",
              j,op->packet[j],(j+no)&0xff);
      exit(1);
    }
}

void check_page(unsigned char *data,const int *header,ogg_page *og){
  long j;
  /* Test data */
  for(j=0;j<og->body_len;j++)
    if(og->body[j]!=data[j]){
      fprintf(stderr,"body data mismatch (2) at pos %ld: %x!=%x!\n\n",
              j,data[j],og->body[j]);
      exit(1);
    }

  /* Test header */
  for(j=0;j<og->header_len;j++){
    if(og->header[j]!=header[j]){
      fprintf(stderr,"header content mismatch at pos %ld:\n",j);
      for(j=0;j<header[26]+27;j++)
        fprintf(stderr," (%ld)%02x:%02x",j,header[j],og->header[j]);
      fprintf(stderr,"\n");
      exit(1);
    }
  }
  if(og->header_len!=header[26]+27){
    fprintf(stderr,"header length incorrect! (%ld!=%d)\n",
            og->header_len,header[26]+27);
    exit(1);
  }
}

void print_header(ogg_page *og){
  int j;
  fprintf(stderr,"\nHEADER:\n");
  fprintf(stderr,"  capture: %c %c %c %c  version: %d  flags: %x\n",
          og->header[0],og->header[1],og->header[2],og->header[3],
          (int)og->header[4],(int)og->header[5]);

  fprintf(stderr,"  granulepos: %d  serialno: %d  pageno: %ld\n",
          ((unsigned)og->header[9]<<24)|(og->header[8]<<16)|
          (og->header[7]<<8)|og->header[6],
          ((unsigned)og->header[17]<<24)|(og->header[16]<<16)|
          (og->header[15]<<8)|og->header[14],
          ((long)((unsigned)og->header[21])<<24)|(og->header[20]<<16)|
          (og->header[19]<<8)|og->header[18]);

  fprintf(stderr,"  checksum: %02x:%02x:%02x:%02x\n  segments: %d (",
          (int)og->header[22],(int)og->header[23],
          (int)og->header[24],(int)og->header[25],
          (int)og->header[26]);

  for(j=27;j<og->header_len;j++)
    fprintf(stderr,"%d ",(int)og->header[j]);
  fprintf(stderr,")\n\n");
}

static int copy_page(ogg_page *og){
  unsigned char *temp=_ogg_malloc(og->header_len);
  if (!temp)
    return -1;
  memcpy(temp,og->header,og->header_len);
  og->header=temp;

  temp=_ogg_malloc(og->body_len);
  if (!temp)
    return -1;
  memcpy(temp,og->body,og->body_len);
  og->body=temp;
  return 0;
}

static void free_page(ogg_page *og){
  _ogg_free (og->header);
  og->header=NULL;
  _ogg_free (og->body);
  og->body=NULL;
}

void error(void){
  fprintf(stderr,"error!\n");
  exit(1);
}

/* 17 only */
const int head1_0[] = {0x4f,0x67,0x67,0x53,0,0x06,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0x15,0xed,0xec,0x91,
                       1,
                       17};

/* 17, 254, 255, 256, 500, 510, 600 byte, pad */
const int head1_1[] = {0x4f,0x67,0x67,0x53,0,0x02,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0x59,0x10,0x6c,0x2c,
                       1,
                       17};
const int head2_1[] = {0x4f,0x67,0x67,0x53,0,0x04,
                       0x07,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,1,0,0,0,
                       0x89,0x33,0x85,0xce,
                       13,
                       254,255,0,255,1,255,245,255,255,0,
                       255,255,90};

/* nil packets; beginning,middle,end */
const int head1_2[] = {0x4f,0x67,0x67,0x53,0,0x02,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0xff,0x7b,0x23,0x17,
                       1,
                       0};
const int head2_2[] = {0x4f,0x67,0x67,0x53,0,0x04,
                       0x07,0x28,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,1,0,0,0,
                       0x5c,0x3f,0x66,0xcb,
                       17,
                       17,254,255,0,0,255,1,0,255,245,255,255,0,
                       255,255,90,0};

/* large initial packet */
const int head1_3[] = {0x4f,0x67,0x67,0x53,0,0x02,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0x01,0x27,0x31,0xaa,
                       18,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,255,10};

const int head2_3[] = {0x4f,0x67,0x67,0x53,0,0x04,
                       0x07,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,1,0,0,0,
                       0x7f,0x4e,0x8a,0xd2,
                       4,
                       255,4,255,0};


/* continuing packet test */
const int head1_4[] = {0x4f,0x67,0x67,0x53,0,0x02,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0xff,0x7b,0x23,0x17,
                       1,
                       0};

const int head2_4[] = {0x4f,0x67,0x67,0x53,0,0x00,
                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                       0x01,0x02,0x03,0x04,1,0,0,0,
                       0xf8,0x3c,0x19,0x79,
                       255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255};

const int head3_4[] = {0x4f,0x67,0x67,0x53,0,0x05,
                       0x07,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,2,0,0,0,
                       0x38,0xe6,0xb6,0x28,
                       6,
                       255,220,255,4,255,0};


/* spill expansion test */
const int head1_4b[] = {0x4f,0x67,0x67,0x53,0,0x02,
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x01,0x02,0x03,0x04,0,0,0,0,
                        0xff,0x7b,0x23,0x17,
                        1,
                        0};

const int head2_4b[] = {0x4f,0x67,0x67,0x53,0,0x00,
                        0x07,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x01,0x02,0x03,0x04,1,0,0,0,
                        0xce,0x8f,0x17,0x1a,
                        23,
                        255,255,255,255,255,255,255,255,
                        255,255,255,255,255,255,255,255,255,10,255,4,255,0,0};


const int head3_4b[] = {0x4f,0x67,0x67,0x53,0,0x04,
                        0x07,0x14,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x01,0x02,0x03,0x04,2,0,0,0,
                        0x9b,0xb2,0x50,0xa1,
                        1,
                        0};

/* page with the 255 segment limit */
const int head1_5[] = {0x4f,0x67,0x67,0x53,0,0x02,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0xff,0x7b,0x23,0x17,
                       1,
                       0};

const int head2_5[] = {0x4f,0x67,0x67,0x53,0,0x00,
                       0x07,0xfc,0x03,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,1,0,0,0,
                       0xed,0x2a,0x2e,0xa7,
                       255,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10,10,
                       10,10,10,10,10,10,10};

const int head3_5[] = {0x4f,0x67,0x67,0x53,0,0x04,
                       0x07,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,2,0,0,0,
                       0x6c,0x3b,0x82,0x3d,
                       1,
                       50};


/* packet that overspans over an entire page */
const int head1_6[] = {0x4f,0x67,0x67,0x53,0,0x02,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0xff,0x7b,0x23,0x17,
                       1,
                       0};

const int head2_6[] = {0x4f,0x67,0x67,0x53,0,0x00,
                       0x07,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,1,0,0,0,
                       0x68,0x22,0x7c,0x3d,
                       255,
                       100,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255};

const int head3_6[] = {0x4f,0x67,0x67,0x53,0,0x01,
                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                       0x01,0x02,0x03,0x04,2,0,0,0,
                       0xf4,0x87,0xba,0xf3,
                       255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255};

const int head4_6[] = {0x4f,0x67,0x67,0x53,0,0x05,
                       0x07,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,3,0,0,0,
                       0xf7,0x2f,0x6c,0x60,
                       5,
                       254,255,4,255,0};

/* packet that overspans over an entire page */
const int head1_7[] = {0x4f,0x67,0x67,0x53,0,0x02,
                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,0,0,0,0,
                       0xff,0x7b,0x23,0x17,
                       1,
                       0};

const int head2_7[] = {0x4f,0x67,0x67,0x53,0,0x00,
                       0x07,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,1,0,0,0,
                       0x68,0x22,0x7c,0x3d,
                       255,
                       100,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255,255,255,
                       255,255,255,255,255,255};

const int head3_7[] = {0x4f,0x67,0x67,0x53,0,0x05,
                       0x07,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
                       0x01,0x02,0x03,0x04,2,0,0,0,
                       0xd4,0xe0,0x60,0xe5,
                       1,
                       0};

int compare_packet(const ogg_packet *op1, const ogg_packet *op2){
  if(op1->packet!=op2->packet){
    fprintf(stderr,"op1->packet != op2->packet\n");
    return(1);
  }
  if(op1->bytes!=op2->bytes){
    fprintf(stderr,"op1->bytes != op2->bytes\n");
    return(1);
  }
  if(op1->b_o_s!=op2->b_o_s){
    fprintf(stderr,"op1->b_o_s != op2->b_o_s\n");
    return(1);
  }
  if(op1->e_o_s!=op2->e_o_s){
    fprintf(stderr,"op1->e_o_s != op2->e_o_s\n");
    return(1);
  }
  if(op1->granulepos!=op2->granulepos){
    fprintf(stderr,"op1->granulepos != op2->granulepos\n");
    return(1);
  }
  if(op1->packetno!=op2->packetno){
    fprintf(stderr,"op1->packetno != op2->packetno\n");
    return(1);
  }
  return(0);
}

void test_pack(const int *pl, const int **headers, int byteskip,
               int pageskip, int packetskip){
  unsigned char *data=_ogg_malloc(1024*1024); /* for scripted test cases only */
  long inptr=0;
  long outptr=0;
  long deptr=0;
  long depacket=0;
  long granule_pos=7,pageno=0;
  int i,j,packets,pageout=pageskip;
  int eosflag=0;
  int bosflag=0;

  int byteskipcount=0;

  if (!data) {
    fprintf(stderr,"unable to allocate required data buffer!\n");
    exit(1);
  }

  ogg_stream_reset(&os_en);
  ogg_stream_reset(&os_de);
  ogg_sync_reset(&oy);

  for(packets=0;packets<packetskip;packets++)
    depacket+=pl[packets];

  for(packets=0;;packets++)if(pl[packets]==-1)break;

  for(i=0;i<packets;i++){
    /* construct a test packet */
    ogg_packet op;
    int len=pl[i];

    op.packet=data+inptr;
    op.bytes=len;
    op.e_o_s=(pl[i+1]<0?1:0);
    op.granulepos=granule_pos;

    granule_pos+=1024;

    for(j=0;j<len;j++)data[inptr++]=i+j;

    /* submit the test packet */
    ogg_stream_packetin(&os_en,&op);

    /* retrieve any finished pages */
    {
      ogg_page og;

      while(ogg_stream_pageout(&os_en,&og)){
        /* We have a page.  Check it carefully */

        fprintf(stderr,"%ld, ",pageno);

        if(headers[pageno]==NULL){
          fprintf(stderr,"coded too many pages!\n");
          exit(1);
        }

        check_page(data+outptr,headers[pageno],&og);

        outptr+=og.body_len;
        pageno++;
        if(pageskip){
          bosflag=1;
          pageskip--;
          deptr+=og.body_len;
        }

        /* have a complete page; submit it to sync/decode */

        {
          ogg_page og_de;
          ogg_packet op_de,op_de2;
          char *buf=ogg_sync_buffer(&oy,og.header_len+og.body_len);
          char *next=buf;
          byteskipcount+=og.header_len;
          if(byteskipcount>byteskip){
            memcpy(next,og.header,byteskipcount-byteskip);
            next+=byteskipcount-byteskip;
            byteskipcount=byteskip;
          }

          byteskipcount+=og.body_len;
          if(byteskipcount>byteskip){
            memcpy(next,og.body,byteskipcount-byteskip);
            next+=byteskipcount-byteskip;
            byteskipcount=byteskip;
          }

          ogg_sync_wrote(&oy,(long)(next-buf));

          while(1){
            int ret=ogg_sync_pageout(&oy,&og_de);
            if(ret==0)break;
            if(ret<0)continue;
            /* got a page.  Happy happy.  Verify that it's good. */

            fprintf(stderr,"(%d), ",pageout);

            check_page(data+deptr,headers[pageout],&og_de);
            deptr+=og_de.body_len;
            pageout++;

            /* submit it to deconstitution */
            ogg_stream_pagein(&os_de,&og_de);

            /* packets out? */
            while(ogg_stream_packetpeek(&os_de,&op_de2)>0){
              ogg_stream_packetpeek(&os_de,NULL);
              ogg_stream_packetout(&os_de,&op_de); /* just catching them all */

              /* verify peek and out match */
              if(compare_packet(&op_de,&op_de2)){
                fprintf(stderr,"packetout != packetpeek! pos=%ld\n",
                        depacket);
                exit(1);
              }

              /* verify the packet! */
              /* check data */
              if(memcmp(data+depacket,op_de.packet,op_de.bytes)){
                fprintf(stderr,"packet data mismatch in decode! pos=%ld\n",
                        depacket);
                exit(1);
              }
              /* check bos flag */
              if(bosflag==0 && op_de.b_o_s==0){
                fprintf(stderr,"b_o_s flag not set on packet!\n");
                exit(1);
              }
              if(bosflag && op_de.b_o_s){
                fprintf(stderr,"b_o_s flag incorrectly set on packet!\n");
                exit(1);
              }
              bosflag=1;
              depacket+=op_de.bytes;

              /* check eos flag */
              if(eosflag){
                fprintf(stderr,"Multiple decoded packets with eos flag!\n");
                exit(1);
              }

              if(op_de.e_o_s)eosflag=1;

              /* check granulepos flag */
              if(op_de.granulepos!=-1){
                fprintf(stderr," granule:%ld ",(long)op_de.granulepos);
              }
            }
          }
        }
      }
    }
  }
  _ogg_free(data);
  if(headers[pageno]!=NULL){
    fprintf(stderr,"did not write last page!\n");
    exit(1);
  }
  if(headers[pageout]!=NULL){
    fprintf(stderr,"did not decode last page!\n");
    exit(1);
  }
  if(inptr!=outptr){
    fprintf(stderr,"encoded page data incomplete!\n");
    exit(1);
  }
  if(inptr!=deptr){
    fprintf(stderr,"decoded page data incomplete!\n");
    exit(1);
  }
  if(inptr!=depacket){
    fprintf(stderr,"decoded packet data incomplete!\n");
    exit(1);
  }
  if(!eosflag){
    fprintf(stderr,"Never got a packet with EOS set!\n");
    exit(1);
  }
  fprintf(stderr,"ok.\n");
}

int main(void){

  ogg_stream_init(&os_en,0x04030201);
  ogg_stream_init(&os_de,0x04030201);
  ogg_sync_init(&oy);

  /* Exercise each code path in the framing code.  Also verify that
     the checksums are working.  */

  {
    /* 17 only */
    const int packets[]={17, -1};
    const int *headret[]={head1_0,NULL};

    fprintf(stderr,"testing single page encoding... ");
    test_pack(packets,headret,0,0,0);
  }

  {
    /* 17, 254, 255, 256, 500, 510, 600 byte, pad */
    const int packets[]={17, 254, 255, 256, 500, 510, 600, -1};
    const int *headret[]={head1_1,head2_1,NULL};

    fprintf(stderr,"testing basic page encoding... ");
    test_pack(packets,headret,0,0,0);
  }

  {
    /* nil packets; beginning,middle,end */
    const int packets[]={0,17, 254, 255, 0, 256, 0, 500, 510, 600, 0, -1};
    const int *headret[]={head1_2,head2_2,NULL};

    fprintf(stderr,"testing basic nil packets... ");
    test_pack(packets,headret,0,0,0);
  }

  {
    /* large initial packet */
    const int packets[]={4345,259,255,-1};
    const int *headret[]={head1_3,head2_3,NULL};

    fprintf(stderr,"testing initial-packet lacing > 4k... ");
    test_pack(packets,headret,0,0,0);
  }

  {
    /* continuing packet test; with page spill expansion, we have to
       overflow the lacing table. */
    const int packets[]={0,65500,259,255,-1};
    const int *headret[]={head1_4,head2_4,head3_4,NULL};

    fprintf(stderr,"testing single packet page span... ");
    test_pack(packets,headret,0,0,0);
  }

  {
    /* spill expand packet test */
    const int packets[]={0,4345,259,255,0,0,-1};
    const int *headret[]={head1_4b,head2_4b,head3_4b,NULL};

    fprintf(stderr,"testing page spill expansion... ");
    test_pack(packets,headret,0,0,0);
  }

  /* page with the 255 segment limit */
  {

    const int packets[]={0,10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,50,-1};
    const int *headret[]={head1_5,head2_5,head3_5,NULL};

    fprintf(stderr,"testing max packet segments... ");
    test_pack(packets,headret,0,0,0);
  }

  {
    /* packet that overspans over an entire page */
    const int packets[]={0,100,130049,259,255,-1};
    const int *headret[]={head1_6,head2_6,head3_6,head4_6,NULL};

    fprintf(stderr,"testing very large packets... ");
    test_pack(packets,headret,0,0,0);
  }

#ifndef DISABLE_CRC
  {
    /* test for the libogg 1.1.1 resync in large continuation bug
       found by Josh Coalson)  */
    const int packets[]={0,100,130049,259,255,-1};
    const int *headret[]={head1_6,head2_6,head3_6,head4_6,NULL};

    fprintf(stderr,"testing continuation resync in very large packets... ");
    test_pack(packets,headret,100,2,3);
  }
#else
    fprintf(stderr,"Skipping continuation resync test due to --disable-crc\n");
#endif

  {
    /* term only page.  why not? */
    const int packets[]={0,100,64770,-1};
    const int *headret[]={head1_7,head2_7,head3_7,NULL};

    fprintf(stderr,"testing zero data page (1 nil packet)... ");
    test_pack(packets,headret,0,0,0);
  }



  {
    /* build a bunch of pages for testing */
    unsigned char *data=_ogg_malloc(1024*1024);
    int pl[]={0, 1,1,98,4079, 1,1,2954,2057, 76,34,912,0,234,1000,1000, 1000,300,-1};
    int inptr=0,i,j;
    ogg_page og[5];

    if (!data) {
      fprintf(stderr,"unable to allocate required packet data buffer!\n");
      exit(1);
    }

    ogg_stream_reset(&os_en);

    for(i=0;pl[i]!=-1;i++){
      ogg_packet op;
      int len=pl[i];

      op.packet=data+inptr;
      op.bytes=len;
      op.e_o_s=(pl[i+1]<0?1:0);
      op.granulepos=(i+1)*1000;

      for(j=0;j<len;j++)data[inptr++]=i+j;
      ogg_stream_packetin(&os_en,&op);
    }

    _ogg_free(data);

    /* retrieve finished pages */
    for(i=0;i<5;i++){
      if(ogg_stream_pageout(&os_en,&og[i])==0){
        fprintf(stderr,"Too few pages output building sync tests!\n");
        exit(1);
      }
      if (-1 == copy_page(&og[i])) {
        fprintf(stderr,"unable to copy page building sync tests!\n");
        exit(1);
      }
    }

    /* Test lost pages on pagein/packetout: no rollback */
    {
      ogg_page temp;
      ogg_packet test;

      fprintf(stderr,"Testing loss of pages... ");

      ogg_sync_reset(&oy);
      ogg_stream_reset(&os_de);
      for(i=0;i<5;i++){
        memcpy(ogg_sync_buffer(&oy,og[i].header_len),og[i].header,
               og[i].header_len);
        ogg_sync_wrote(&oy,og[i].header_len);
        memcpy(ogg_sync_buffer(&oy,og[i].body_len),og[i].body,og[i].body_len);
        ogg_sync_wrote(&oy,og[i].body_len);
      }

      ogg_sync_pageout(&oy,&temp);
      ogg_stream_pagein(&os_de,&temp);
      ogg_sync_pageout(&oy,&temp);
      ogg_stream_pagein(&os_de,&temp);
      ogg_sync_pageout(&oy,&temp);
      /* skip */
      ogg_sync_pageout(&oy,&temp);
      ogg_stream_pagein(&os_de,&temp);

      /* do we get the expected results/packets? */

      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,0,0,0);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,1,1,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,1,2,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,98,3,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,4079,4,5000);
      if(ogg_stream_packetout(&os_de,&test)!=-1){
        fprintf(stderr,"Error: loss of page did not return error\n");
        exit(1);
      }
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,76,9,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,34,10,-1);
      fprintf(stderr,"ok.\n");
    }

    /* Test lost pages on pagein/packetout: rollback with continuation */
    {
      ogg_page temp;
      ogg_packet test;

      fprintf(stderr,"Testing loss of pages (rollback required)... ");

      ogg_sync_reset(&oy);
      ogg_stream_reset(&os_de);
      for(i=0;i<5;i++){
        memcpy(ogg_sync_buffer(&oy,og[i].header_len),og[i].header,
               og[i].header_len);
        ogg_sync_wrote(&oy,og[i].header_len);
        memcpy(ogg_sync_buffer(&oy,og[i].body_len),og[i].body,og[i].body_len);
        ogg_sync_wrote(&oy,og[i].body_len);
      }

      ogg_sync_pageout(&oy,&temp);
      ogg_stream_pagein(&os_de,&temp);
      ogg_sync_pageout(&oy,&temp);
      ogg_stream_pagein(&os_de,&temp);
      ogg_sync_pageout(&oy,&temp);
      ogg_stream_pagein(&os_de,&temp);
      ogg_sync_pageout(&oy,&temp);
      /* skip */
      ogg_sync_pageout(&oy,&temp);
      ogg_stream_pagein(&os_de,&temp);

      /* do we get the expected results/packets? */

      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,0,0,0);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,1,1,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,1,2,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,98,3,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,4079,4,5000);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,1,5,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,1,6,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,2954,7,-1);
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,2057,8,9000);
      if(ogg_stream_packetout(&os_de,&test)!=-1){
        fprintf(stderr,"Error: loss of page did not return error\n");
        exit(1);
      }
      if(ogg_stream_packetout(&os_de,&test)!=1)error();
      checkpacket(&test,300,17,18000);
      fprintf(stderr,"ok.\n");
    }

    /* the rest only test sync */
    {
      ogg_page og_de;
      /* Test fractional page inputs: incomplete capture */
      fprintf(stderr,"Testing sync on partial inputs... ");
      ogg_sync_reset(&oy);
      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header,
             3);
      ogg_sync_wrote(&oy,3);
      if(ogg_sync_pageout(&oy,&og_de)>0)error();

      /* Test fractional page inputs: incomplete fixed header */
      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header+3,
             20);
      ogg_sync_wrote(&oy,20);
      if(ogg_sync_pageout(&oy,&og_de)>0)error();

      /* Test fractional page inputs: incomplete header */
      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header+23,
             5);
      ogg_sync_wrote(&oy,5);
      if(ogg_sync_pageout(&oy,&og_de)>0)error();

      /* Test fractional page inputs: incomplete body */

      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header+28,
             og[1].header_len-28);
      ogg_sync_wrote(&oy,og[1].header_len-28);
      if(ogg_sync_pageout(&oy,&og_de)>0)error();

      memcpy(ogg_sync_buffer(&oy,og[1].body_len),og[1].body,1000);
      ogg_sync_wrote(&oy,1000);
      if(ogg_sync_pageout(&oy,&og_de)>0)error();

      memcpy(ogg_sync_buffer(&oy,og[1].body_len),og[1].body+1000,
             og[1].body_len-1000);
      ogg_sync_wrote(&oy,og[1].body_len-1000);
      if(ogg_sync_pageout(&oy,&og_de)<=0)error();

      fprintf(stderr,"ok.\n");
    }

    /* Test fractional page inputs: page + incomplete capture */
    {
      ogg_page og_de;
      fprintf(stderr,"Testing sync on 1+partial inputs... ");
      ogg_sync_reset(&oy);

      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header,
             og[1].header_len);
      ogg_sync_wrote(&oy,og[1].header_len);

      memcpy(ogg_sync_buffer(&oy,og[1].body_len),og[1].body,
             og[1].body_len);
      ogg_sync_wrote(&oy,og[1].body_len);

      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header,
             20);
      ogg_sync_wrote(&oy,20);
      if(ogg_sync_pageout(&oy,&og_de)<=0)error();
      if(ogg_sync_pageout(&oy,&og_de)>0)error();

      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header+20,
             og[1].header_len-20);
      ogg_sync_wrote(&oy,og[1].header_len-20);
      memcpy(ogg_sync_buffer(&oy,og[1].body_len),og[1].body,
             og[1].body_len);
      ogg_sync_wrote(&oy,og[1].body_len);
      if(ogg_sync_pageout(&oy,&og_de)<=0)error();

      fprintf(stderr,"ok.\n");
    }

    /* Test recapture: garbage + page */
    {
      ogg_page og_de;
      fprintf(stderr,"Testing search for capture... ");
      ogg_sync_reset(&oy);

      /* 'garbage' */
      memcpy(ogg_sync_buffer(&oy,og[1].body_len),og[1].body,
             og[1].body_len);
      ogg_sync_wrote(&oy,og[1].body_len);

      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header,
             og[1].header_len);
      ogg_sync_wrote(&oy,og[1].header_len);

      memcpy(ogg_sync_buffer(&oy,og[1].body_len),og[1].body,
             og[1].body_len);
      ogg_sync_wrote(&oy,og[1].body_len);

      memcpy(ogg_sync_buffer(&oy,og[2].header_len),og[2].header,
             20);
      ogg_sync_wrote(&oy,20);
      if(ogg_sync_pageout(&oy,&og_de)>0)error();
      if(ogg_sync_pageout(&oy,&og_de)<=0)error();
      if(ogg_sync_pageout(&oy,&og_de)>0)error();

      memcpy(ogg_sync_buffer(&oy,og[2].header_len),og[2].header+20,
             og[2].header_len-20);
      ogg_sync_wrote(&oy,og[2].header_len-20);
      memcpy(ogg_sync_buffer(&oy,og[2].body_len),og[2].body,
             og[2].body_len);
      ogg_sync_wrote(&oy,og[2].body_len);
      if(ogg_sync_pageout(&oy,&og_de)<=0)error();

      fprintf(stderr,"ok.\n");
    }

#ifndef DISABLE_CRC
    /* Test recapture: page + garbage + page */
    {
      ogg_page og_de;
      fprintf(stderr,"Testing recapture... ");
      ogg_sync_reset(&oy);

      memcpy(ogg_sync_buffer(&oy,og[1].header_len),og[1].header,
             og[1].header_len);
      ogg_sync_wrote(&oy,og[1].header_len);

      memcpy(ogg_sync_buffer(&oy,og[1].body_len),og[1].body,
             og[1].body_len);
      ogg_sync_wrote(&oy,og[1].body_len);

      memcpy(ogg_sync_buffer(&oy,og[2].header_len),og[2].header,
             og[2].header_len);
      ogg_sync_wrote(&oy,og[2].header_len);

      memcpy(ogg_sync_buffer(&oy,og[2].header_len),og[2].header,
             og[2].header_len);
      ogg_sync_wrote(&oy,og[2].header_len);

      if(ogg_sync_pageout(&oy,&og_de)<=0)error();

      memcpy(ogg_sync_buffer(&oy,og[2].body_len),og[2].body,
             og[2].body_len-5);
      ogg_sync_wrote(&oy,og[2].body_len-5);

      memcpy(ogg_sync_buffer(&oy,og[3].header_len),og[3].header,
             og[3].header_len);
      ogg_sync_wrote(&oy,og[3].header_len);

      memcpy(ogg_sync_buffer(&oy,og[3].body_len),og[3].body,
             og[3].body_len);
      ogg_sync_wrote(&oy,og[3].body_len);

      if(ogg_sync_pageout(&oy,&og_de)>0)error();
      if(ogg_sync_pageout(&oy,&og_de)<=0)error();

      fprintf(stderr,"ok.\n");
    }
#else
    fprintf(stderr,"Skipping recapture test due to --disable-crc\n");
#endif

    /* Free page data that was previously copied */
    {
      for(i=0;i<5;i++){
        free_page(&og[i]);
      }
    }
  }
  ogg_sync_clear(&oy);
  ogg_stream_clear(&os_en);
  ogg_stream_clear(&os_de);

  return(0);
}

