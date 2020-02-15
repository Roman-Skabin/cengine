//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "graphics/renderer.h"

typedef struct RasterizerOutput
{
    union
    {
        v2s xy;
        struct
        {
            s32 x;
            s32 y;
        };
    };
    f32 z;
} RasterizerOutput;

CEXTERN BUF RasterizerOutput *RasterizeTriangle(EngineState *state, v4 p1, v4 p2, v4 p3);