//
// Copyright 2020 Roman Skabin
//

#include "core/pch.h"
#include "core/common.h"
#include "tools/critical_section.hpp"

namespace REV
{

REV_GLOBAL HANDLE                 g_Console         = GetStdHandle(STD_OUTPUT_HANDLE);
REV_GLOBAL CriticalSection<false> g_CriticalSection;

void REV_CDECL DebugF(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[2048] = {'\0'};
    int len           = vsprintf(buffer, format, args);
    buffer[len++]     = '\n';

    g_CriticalSection.Enter();
    REV_DEBUG_RESULT(WriteConsoleA(g_Console, buffer, len, null, null));
    OutputDebugStringA(buffer);
    g_CriticalSection.Leave();

    va_end(args);
}

void REV_CDECL DebugFC(DEBUG_COLOR color, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[2048] = {'\0'};
    int len           = vsprintf(buffer, format, args);
    buffer[len++]     = '\n';

    g_CriticalSection.Enter();
    REV_DEBUG_RESULT(SetConsoleTextAttribute(g_Console, cast<u16>(color)));
    REV_DEBUG_RESULT(WriteConsoleA(g_Console, buffer, len, null, null));
    REV_DEBUG_RESULT(SetConsoleTextAttribute(g_Console, cast<u16>(DEBUG_COLOR::INFO)));
    OutputDebugStringA(buffer);
    g_CriticalSection.Leave();

    va_end(args);
}

void REV_CDECL PrintDebugMessage(const char *file, u64 line, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char message[2048] = {'\0'};

    if (args)
    {
        int len = sprintf(message, "%s(%I64u): REV_CHECK failed: ", file, line);
        len += vsprintf(message + len, format, args);

        g_CriticalSection.Enter();
        SetConsoleTextAttribute(g_Console, cast<u16>(DEBUG_COLOR::ERROR));
        WriteConsoleA(g_Console, message, len, null, null);
        SetConsoleTextAttribute(g_Console, cast<u16>(DEBUG_COLOR::INFO));
        OutputDebugStringA(message);
        g_CriticalSection.Leave();

        va_end(args);
    }
    else
    {
        int len = sprintf(message, "%s(%I64u): REV_CHECK failed: %s\n", file, line, format);

        g_CriticalSection.Enter();
        SetConsoleTextAttribute(g_Console, cast<u16>(DEBUG_COLOR::ERROR));
        WriteConsoleA(g_Console, message, len, null, null);
        SetConsoleTextAttribute(g_Console, cast<u16>(DEBUG_COLOR::INFO));
        OutputDebugStringA(message);
        g_CriticalSection.Leave();
    }
}

}
