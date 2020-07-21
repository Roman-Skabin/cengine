//
// Copyright 2020 Roman Skabin
//

#include "core/pch.h"
#include "core/core.h"

//
// Debuging
//

global HANDLE gConsole;

void __cdecl DebugF(DEBUG_IN debug_in, const char *format, ...)
{
    if (!gConsole)
    {
        gConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    va_list args;
    va_start(args, format);

    char buffer[BUFSIZ] = {'\0'};
    int len             = vsprintf(buffer, format, args);
    buffer[len]         = '\n';

    if (debug_in & DEBUG_IN_CONSOLE)
    {
        WriteConsoleA(gConsole, buffer, len, 0, 0);
    }
    if (debug_in & DEBUG_IN_DEBUG)
    {
        OutputDebugStringA(buffer);
    }

    va_end(args);
}

void __cdecl MessageF(MESSAGE_TYPE type, const char *format, ...)
{
    char title[64] = {0};

    switch (type)
    {
        case MESSAGE_TYPE_ERROR:
        {
            sprintf(title, "Error: 0x%08I32X!", GetLastError());
        } break;
        
        case MESSAGE_TYPE_WARNING:
        {
            CopyMemory(title, "Warning", CSTRLEN("Warning"));
        } break;

        case MESSAGE_TYPE_INFO:
        {
            CopyMemory(title, "Info", CSTRLEN("Info"));
        } break;
    }

    va_list args;
    va_start(args, format);

    if (args)
    {
        char buffer[BUFSIZ] = {'\0'};
        int  len            = vsprintf(buffer, format, args);

        MessageBoxA(null, buffer, title, MB_OK | type);

        va_end(args);
    }
    else
    {
        MessageBoxA(null, format, title, MB_OK | type);
    }

    if (type == MESSAGE_TYPE_ERROR)
    {
        ExitProcess(1);
    }
}

void ShowDebugMessage(
    IN       b32         message_is_expr,
    IN       const char *file,
    IN       u64         line,
    IN       const char *function,
    IN       const char *title,
    IN       const char *format,
    OPTIONAL ...)
{
    // @Important(Roman): last_error has to be placed
    //                    before everything else.
    u32 last_error = GetLastError();

    char box_title[64];
    sprintf(box_title, "%s: 0x%08I32X!", title, last_error);

    va_list args;
    va_start(args, format);

    if (!message_is_expr && args)
    {
        char message[1024];
        vsprintf(message, format, args);

        const char *box_message_format =
        "MESSAGE: %s\n\n"
        "FILE: %s(%I64u)\n\n"
        "FUNCTION: %s";

        char box_message[2048];
        sprintf(box_message, box_message_format, message, file, line, function);

        MessageBoxA(null, box_message, box_title, MB_OK | MB_ICONERROR);

        va_end(args);
    }
    else if (!message_is_expr)
    {
        const char *box_message_format =
        "MESSAGE: %s\n\n"
        "FILE: %s(%I64u)\n\n"
        "FUNCTION: %s";

        char box_message[2048];
        sprintf(box_message, box_message_format, format, file, line, function);

        MessageBoxA(null, box_message, box_title, MB_OK | MB_ICONERROR);
    }
    else
    {
        const char *box_message_format =
        "EXPRESSION: %s\n\n"
        "FILE: %s(%I64u)\n\n"
        "FUNCTION: %s";

        char box_message[2048];
        sprintf(box_message, box_message_format, format, file, line, function);

        MessageBoxA(null, box_message, box_title, MB_OK | MB_ICONERROR);
    }
}
