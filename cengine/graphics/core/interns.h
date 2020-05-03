//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "tools/buffer.h"
#include "core/memory.h"

#ifndef ENGINE_DEFINED
#define ENGINE_DEFINED
    typedef struct Engine Engine;
#endif

typedef struct Intern
{
    const char *str;
    u64 len;
} Intern;

typedef struct Interns
{
    BUF Intern *interns;
    Memory     *memory;
} Interns;

CENGINE_FUN void CreateInterns(Engine *engine, Interns *interns);
CENGINE_FUN void DestroyInterns(Interns *interns);

CENGINE_FUN const char *InternStringRange(Interns *interns, const char *start, const char *end);
#define InternString(interns, string, length) InternStringRange(interns, string, (string) + (length))
#define InternCSTR(interns, cstr)             InternString(interns, cstr, CSTRLEN(cstr))
