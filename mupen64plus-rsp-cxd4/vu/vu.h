/******************************************************************************\
* Project:  MSP Emulation Layer for Vector Unit Computational Operations       *
* Authors:  Iconoclast                                                         *
* Release:  2013.11.26                                                         *
* License:  CC0 Public Domain Dedication                                       *
*                                                                              *
* To the extent possible under law, the author(s) have dedicated all copyright *
* and related and neighboring rights to this software to the public domain     *
* worldwide. This software is distributed without any warranty.                *
*                                                                              *
* You should have received a copy of the CC0 Public Domain Dedication along    *
* with this software.                                                          *
* If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.             *
\******************************************************************************/
#ifndef _VU_H
#define _VU_H

#if defined(ARCH_MIN_SSE2)
#include <emmintrin.h>

#define _mm_cmple_epu16(dst, src) _mm_cmpeq_epi16(_mm_subs_epu16(dst, src), _mm_setzero_si128())
#define _mm_cmpgt_epu16(dst, src) _mm_andnot_si128(_mm_cmpeq_epi16(dst, src), _mm_cmple_epu16(src, dst))
#define _mm_cmplt_epu16(dst, src) _mm_cmpgt_epu16(src, dst)
#define _mm_mullo_epu16(dst, src) _mm_mullo_epi16(dst, src)
#endif

/*
 * accumulator-indexing macros (inverted access dimensions, suited for SSE)
 */
#define HI      00
#define MD      01
#define LO      02

#define VACC_L      (VACC[LO])
#define VACC_M      (VACC[MD])
#define VACC_H      (VACC[HI])

#define ACC_L(i)    (VACC_L[i])
#define ACC_M(i)    (VACC_M[i])
#define ACC_H(i)    (VACC_H[i])

#include "shuffle.h"
#include "clamp.h"
#include "cf.h"

static void res_V(int vd, int vs, int vt, int e)
{
   register int i;

   vs = vt = e = 0;
   if (vs != vt || vt != e)
      return;
   /* C2, RESERVED */
   /* uncertain how to handle reserved, untested */
   for (i = 0; i < N; i++)
      VR[vd][i] = 0x0000; /* override behavior (bpoint) */
}

static void res_M(int vd, int vs, int vt, int e)
{
   /* VMUL IQ */
   res_V(vd, vs, vt, e);
   /* Ultra64 OS did have these, so one could implement this ext. */
}

#include "add.h"
#include "logical.h"
#include "divide.h"
#include "select.h"
#include "multiply.h"

static void (*COP2_C2[64])(int, int, int, int) = {
    VMULF  ,VMULU  ,res_M  ,res_M  ,VMUDL  ,VMUDM  ,VMUDN  ,VMUDH  , /* 000 */
    VMACF  ,VMACU  ,res_M  ,res_M  ,VMADL  ,VMADM  ,VMADN  ,VMADH  , /* 001 */
    VADD   ,VSUB   ,res_V  ,VABS   ,VADDC  ,VSUBC  ,res_V  ,res_V  , /* 010 */
    res_V  ,res_V  ,res_V  ,res_V  ,res_V  ,VSAW   ,res_V  ,res_V  , /* 011 */
    VLT    ,VEQ    ,VNE    ,VGE    ,VCL    ,VCH    ,VCR    ,VMRG   , /* 100 */
    VAND   ,VNAND  ,VOR    ,VNOR   ,VXOR   ,VNXOR  ,res_V  ,res_V  , /* 101 */
    VRCP   ,VRCPL  ,VRCPH  ,VMOV   ,VRSQ   ,VRSQL  ,VRSQH  ,VNOP   , /* 110 */
    res_V  ,res_V  ,res_V  ,res_V  ,res_V  ,res_V  ,res_V  ,res_V  , /* 111 */
}; /* 000     001     010     011     100     101     110     111 */
#endif
