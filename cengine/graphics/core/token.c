//
// Copyright 2020 Roman Skabin
//

#include "core/pch.h"
#include "graphics/core/shader_parser.h"

#define SyntaxError(format, ...) MessageF(MESSAGE_TYPE_ERROR, CSTRCAT("Shader syntax error: ", format), __VA_ARGS__)

const char *TokenKindName(ShaderLexer *lexer, TOKEN_KIND kind)
{
    if (kind < lexer->token_kind_names_count)
    {
        const char *name = lexer->token_kind_names[kind];
        return name ? name : "<unknown>";
    }
    else
    {
        return "<unknown>";
    }
}

const char *TokenInfo(ShaderLexer *lexer)
{
    if (lexer->token.kind == TOKEN_KIND_NAME
    ||  lexer->token.kind == TOKEN_KIND_KEYWORD)
    {
        return lexer->token.name;
    }
    else
    {
        return TokenKindName(lexer, lexer->token.kind);
    }
}

void CheckToken(ShaderLexer *lexer, TOKEN_KIND kind)
{
    if (lexer->token.kind != kind)
    {
        SyntaxError("expected '%s', got '%s'.",
                    TokenKindName(lexer, kind),
                    TokenInfo(lexer));
    }
}
