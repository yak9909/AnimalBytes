#include <string>
#include <CTRPluginFramework.hpp>
#include "types.h"

#include "ScriptEngine/Types/Token.h"

#include "ScriptEngine/Lexer.h"
#include "ScriptEngine/Exceptions.h"

static char const* punctuaters[] = {
  "("
  ")"
  "+"
  "-"
  "*"
  "/"
};

namespace CTRPluginFramework::ScriptEngine {
  Lexer::Lexer(std::string const& source)
    : source(source),
      position(0)
  {
  }
  
  Token* Lexer::run() {
    Token top{ TOK_INT };
    Token* cur = &top;

    pass_space();
    while( check() ) {
      char ch = peek();
      size_t pos = position;
      char const* str = source.data() + pos;

      cur = new Token(TOK_INT, cur, pos);
      cur->pos = pos;

      if( isdigit(ch) ) {
        while( check() && isdigit(peek()) ) {
          position++;
        }
      }
      else if( isalpha(ch) || ch == '_' ) {
        while( check() && (isalnum(ch = peek()) || ch == '_') ) {
          position++;
        }
      }
      else {
        for( std::string_view&& pu : punctuaters ) {
          if( match(pu) ) {
            position += pu.length();
            cur->kind = TOK_PUNCTUATER;
            goto found;
          }
        }

        throw new LexError(pos, "unknown token");

      found:;
      }

      cur->str = { str + pos, position - pos };
      pass_space();
    }

    cur = new Token(TOK_END, cur, position);
    return top.next;
  }

  bool Lexer::check() {
    return position < source.length();
  }

  char Lexer::peek() {
    return source[position];
  }

  bool Lexer::match(std::string_view s) {
    return strncmp(source.data() + position, s.data(), s.length());
  }

  void Lexer::pass_space() {
    while( check() && peek() <= ' ' ) {
      position++;
    }
  }
}