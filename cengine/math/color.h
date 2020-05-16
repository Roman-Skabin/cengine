//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "math/vec.h"

CENGINE_DATA const v4 gBlackA0;
CENGINE_DATA const v4 gRedA0;
CENGINE_DATA const v4 gGreenA0;
CENGINE_DATA const v4 gBlueA0;
CENGINE_DATA const v4 gYellowA0;
CENGINE_DATA const v4 gMagentaA0;
CENGINE_DATA const v4 gCyanA0;
CENGINE_DATA const v4 gWhiteA0;

CENGINE_DATA const v4 gBlackA1;
CENGINE_DATA const v4 gRedA1;
CENGINE_DATA const v4 gGreenA1;
CENGINE_DATA const v4 gBlueA1;
CENGINE_DATA const v4 gYellowA1;
CENGINE_DATA const v4 gMagentaA1;
CENGINE_DATA const v4 gCyanA1;
CENGINE_DATA const v4 gWhiteA1;

// @NOTE(Roamn): Everything below is legacy from software rendering times.
//               Btw it's not deprecated so you can use it as well.

//
// norm_to_*
//

INLINE u32 MATH_CALL norm_to_hex(v4 color)
{
    __m128i mm = _mm_cvtps_epi32(
                     _mm_mul_ps(
                         _mm_set_ps1(255.0f),
                         _mm_max_ps(
                             _mm_setzero_ps(),
                             _mm_min_ps(
                                 _mm_set_ps1(1.0f),
                                 color.mm))));
    return (MMu(mm, 3) << 24)
         | (MMu(mm, 0) << 16)
         | (MMu(mm, 1) <<  8)
         | (MMu(mm, 2)      );
}

INLINE v4 MATH_CALL norm_to_v4(v4 color)
{
    v4 out;
    out.mm = _mm_mul_ps(
                 _mm_set_ps1(255.0f),
                 _mm_max_ps(
                     _mm_setzero_ps(),
                     _mm_min_ps(
                         _mm_set_ps1(1.0f),
                         color.mm)));
    return out;
}

INLINE v4u MATH_CALL norm_to_v4u(v4 color)
{
    v4u out;
    out.mm = _mm_cvtps_epi32(
                 _mm_mul_ps(
                     _mm_set_ps1(255.0f),
                     _mm_max_ps(
                         _mm_setzero_ps(),
                         _mm_min_ps(
                             _mm_set_ps1(1.0f),
                             color.mm))));
    return out;
}

//
// v4_to_*
//

INLINE v4 MATH_CALL v4_to_norm(v4 color)
{
    v4 out;
    out.mm = _mm_div_ps(
                 _mm_cvtepi32_ps(
                     _mm_and_si128(
                         _mm_cvtps_epi32(color.mm),
                         _mm_set1_epi32(0xFF))),
                 _mm_set_ps1(255.0f));
    return out;
}

INLINE u32 MATH_CALL v4_to_hex(v4 color)
{
    __m128i mm = _mm_cvtps_epi32(color.mm);
    return (MMu(mm, 3) << 24)
         | (MMu(mm, 0) << 16)
         | (MMu(mm, 1) <<  8)
         | (MMu(mm, 2)      );
}

//
// hex_to_*
//

INLINE v4 MATH_CALL hex_to_norm(u32 color)
{
    v4 out;
    out.mm = _mm_div_ps(
                 _mm_cvtepi32_ps(
                     _mm_and_si128(
                         _mm_setr_epi32(color >> 16, color >> 8, color, color >> 24),
                         _mm_set1_epi32(0xFF))),
                 _mm_set_ps1(255.0f));
    return out;
}

INLINE v4 MATH_CALL hex_to_v4(u32 color)
{
    v4 out;
    out.mm = _mm_cvtepi32_ps(
                 _mm_and_si128(
                     _mm_setr_epi32(color >> 16, color >> 8, color, color >> 24),
                     _mm_set1_epi32(0xFF)));
    return out;
}

INLINE v4u MATH_CALL hex_to_v4u(u32 color)
{
    v4u out;
    out.mm = _mm_and_si128(
                 _mm_setr_epi32(color >> 16, color >> 8, color, color >> 24),
                 _mm_set1_epi32(0xFF));
    return out;
}

//
// v4u_to_*
//

INLINE v4 MATH_CALL v4u_to_norm(v4u color)
{
    v4 out;
    out.mm = _mm_div_ps(
                 _mm_cvtepi32_ps(
                     _mm_and_si128(
                         color.mm,
                         _mm_set1_epi32(0xFF))),
                 _mm_set_ps1(255.0f));
    return out;
}

INLINE u32 MATH_CALL v4u_to_hex(v4u color)
{
    return (MMu(color.mm, 3) << 24)
         | (MMu(color.mm, 0) << 16)
         | (MMu(color.mm, 1) <<  8)
         | (MMu(color.mm, 2)      );
}