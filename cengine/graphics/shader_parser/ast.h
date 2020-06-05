//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "tools/buffer.h"
#include "math/vec.h"

#define ExtendsList(Type) Type *next;

typedef struct ASTType        ASTType;
typedef struct ASTStruct      ASTStruct;
typedef struct ASTStructField ASTStructField;

typedef enum AST_TYPE_KIND
{
    AST_TYPE_KIND_SCALAR,
    AST_TYPE_KIND_VECTOR,
    AST_TYPE_KIND_MATRIX,
    AST_TYPE_KIND_ARRAY,
    AST_TYPE_KIND_STRUCT,
} AST_TYPE_KIND;

typedef enum AST_TYPE_FLAG
{
    AST_TYPE_FLAG_NONE,
    AST_TYPE_FLAG_SINT,
    AST_TYPE_FLAG_UINT,
    AST_TYPE_FLAG_HALF,
    AST_TYPE_FLAG_FLOAT,
} AST_TYPE_FLAG;

struct ASTType
{
    ExtendsList(ASTType)
    ASTType       *base_type;
    const char    *name;
    AST_TYPE_KIND  kind;
    DXGI_FORMAT    format;
    AST_TYPE_FLAG  flag;
    b32            builtin;
    u64            size_in_bytes;
    union
    {
        u32 dimension;
        v2u mat_size;
        ASTStruct *_struct;
    };
};

struct ASTStructField
{
    ExtendsList(ASTStructField)
    ASTType    *type;
    const char *semantic_name;
    u32         semantic_index;
};

struct ASTStruct
{
    ExtendsList(ASTStruct)
    const char     *name;
    ASTStructField *fields;
    u64             fields_count;
};