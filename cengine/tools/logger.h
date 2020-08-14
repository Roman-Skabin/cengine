//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "core/core.h"

typedef enum LOG_TO
{
    LOG_TO_FILE    = BIT(1),
    LOG_TO_CONSOLE = BIT(2),
    LOG_TO_DEBUG   = BIT(3),
} LOG_TO;

typedef struct Logger
{
    const char *name;
    HANDLE      file;
    HANDLE      console;
    LOG_TO      log_to;
    union
    {
        u16 full;
        struct
        {
            u8 high;
            u8 low;
        };
    } attribs;
} Logger;

CENGINE_FUN void CreateLogger(
    in  const char *name,
    opt const char *filename, // @NOTE(Roman): Required if you are logging to the file
    in  LOG_TO      log_to,
    out Logger     *logger
);

// @NOTE(Roman): <dest> logs to the exactly same file as a <src>
CENGINE_FUN void DuplicateLogger(
    in  const char *name,
    in  LOG_TO      log_to, // @NOTE(Roman): LOG_TO_FILE flag is required
    in  Logger     *src,    // @NOTE(Roman): Has to get LOG_TO_FILE flag
    out Logger     *dest
);

CENGINE_FUN void DestroyLogger(
    in Logger *logger
);

typedef enum LOG_KIND
{
    LOG_KIND_INFO,
    LOG_KIND_SUCCESS,
    LOG_KIND_WARNING,
    LOG_KIND_ERROR,
} LOG_KIND;

CENGINE_FUN void __cdecl LoggerLog(
    in  Logger     *logger,
    in  LOG_KIND    log_kind,
    in  const char *format,
    opt ...
);

#define LogInfo(logger, format, ...)    LoggerLog(logger, LOG_KIND_INFO,    format, __VA_ARGS__)
#define LogSuccess(logger, format, ...) LoggerLog(logger, LOG_KIND_SUCCESS, format, __VA_ARGS__)
#define LogWarning(logger, format, ...) LoggerLog(logger, LOG_KIND_WARNING, format, __VA_ARGS__)
#define LogError(logger, format, ...)   LoggerLog(logger, LOG_KIND_ERROR,   format, __VA_ARGS__)
