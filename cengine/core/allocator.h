//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "core/core.h"

#if DEBUG
    CENGINE_DATA u64 gAllocationsPerFrame;
    CENGINE_DATA u64 gReAllocationsPerFrame;
    CENGINE_DATA u64 gDeAllocationsPerFrame;
#endif

typedef struct BlockHeader BlockHeader;

typedef struct Allocator
{
    // @NOTE(Roman): Just saved pointers to destroyed blocks.
    // @TODO(Roman): BlockHeader *free_list;

    BlockHeader *base;
    u64          used;
    u64          cap;
    b32          reserved;
} Allocator;

CENGINE_FUN void CreateAllocator(
    in  Allocator *allocator,
    opt void      *base_address,
    in  u64        capacity,
    in  b32        clear_memory // @NOTE(Roman): There is a sence to use it only if base_address = null.
);

CENGINE_FUN void DestroyAllocator(
    in Allocator *allocator
);

CENGINE_FUN void *Allocate(
    in Allocator *allocator,
    in u64        bytes
);

CENGINE_FUN void DeAllocate(
    in Allocator  *allocator,
    in void      **mem
);

CENGINE_FUN void *ReAllocate(
    in  Allocator  *allocator,
    opt void      **mem,       // @NOTE(Roman): if mem or *mem = null then Allocate returns.
    opt u64         bytes      // @NOTE(Roman): if bytes = 0 then *mem will be deallocated.
);

CENGINE_FUN void *AllocateAligned(
    in  Allocator *allocator,
    in  u64        bytes,
    opt u64        alignment
);

CENGINE_FUN void DeAllocateAligned(
    in Allocator  *allocator,
    in void      **mem
);

CENGINE_FUN void *ReAllocateAligned(
    in  Allocator  *allocator,
    opt void      **mem,       // @NOTE(Roman): if mem or *mem = null then Allocate returns.
    opt u64         bytes,     // @NOTE(Roman): if bytes = 0 then *mem will be deallocated.
    opt u64         alignment
);

#define   Alloc(Type, allocator, count)      cast(Type *, Allocate(allocator, sizeof(Type) * (count)))
#define DeAlloc(allocator, mem)              DeAllocate(allocator, &(mem))
#define ReAlloc(Type, allocator, mem, count) cast(Type *, ReAllocate(allocator, &(mem), sizeof(Type) * (count)))

#define   AllocA(Type, allocator, count, alignment)      cast(Type *, AllocateAligned(allocator, sizeof(Type) * (count), alignment))
#define DeAllocA(allocator, mem)                         DeAllocateAligned(allocator, &(mem))
#define ReAllocA(Type, allocator, mem, count, alignment) cast(Type *, ReAllocateAligned(allocator, &(mem), sizeof(Type) * (count), alignment))
