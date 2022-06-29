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
    Token* next;
  };
}