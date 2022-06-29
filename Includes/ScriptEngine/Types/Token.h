#pragma once

#include "types.h"
#include <string>

namespace CTRPluginFramework::ScriptEngine {
  enum TokenKind {
    TOK_INT,
    TOK_IDENT,
    TOK_PUNCTUATER,
    TOK_END
  };

  struct Token {
    TokenKind kind;
    std::string_view str;
    Token* next;
    size_t pos;

    explicit Token(TokenKind kind);
    Token(TokenKind kind, Token* prev, size_t pos);
  };
}