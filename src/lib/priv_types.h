#ifndef PRIV_TYPES_H
#define PRIV_TYPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <math.h>

#define samp_per_frame2  576

#include "types.h"
#include "bitstream.h"
#include "priv_layer3.h"

/* #define DEBUG if you want the library to dump info to stdout */

#define false 0
#define true 1

#define PI          3.14159265358979
#define PI4         0.78539816339745
#define PI12        0.26179938779915
#define PI36        0.087266462599717
#define PI64        0.049087385212
#define SQRT2       1.41421356237
#define LN2         0.69314718
#define LN_TO_LOG10 0.2302585093
#define BLKSIZE     1024
#define HAN_SIZE    512
#define SCALE_BLOCK 12
#define SCALE_RANGE 64
#define SCALE       32768
#define SBLIMIT     32

#ifndef bool
typedef unsigned char bool;
#endif

typedef struct {
    int    mode;      /* + */ /* Stereo mode */
    int    bitr;      /* + */ /* Must conform to known bitrate - see Main.c */
    int    emph;      /* + */ /* De-emphasis */
    int    padding;
    long   bits_per_frame;
    long   bits_per_slot;
    double frac_slots_per_frame;
    double slot_lag;
    int    whole_slots_per_frame;
    int    bitrate_index;     /* + */ /* See Main.c and Layer3.c */
    int    samplerate_index;  /* + */ /* See Main.c and Layer3.c */
    int    crc;
    int    ext;
    int    mode_ext;
    int    copyright;  /* + */
    int    original;   /* + */
} priv_mpeg_t;

typedef struct {
  wave_t         wave;
  priv_mpeg_t    mpeg;
  bitstream_t    bs;
  L3_side_info_t side_info;
  int            sideinfo_len;
  int            mean_bits;
  L3_psy_ratio_t ratio;
  L3_scalefac_t  scalefactor;
  short          *buffer_window[2];
  short          buffer[2][samp_per_frame];
  double         pe[2][2];
  int            l3_enc[2][2][samp_per_frame2];
  long           l3_sb_sample[2][3][18][SBLIMIT];
  long           mdct_freq[2][2][samp_per_frame2];

} encoder_t;

#endif