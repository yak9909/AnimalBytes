#include <string>
#include <vector>
#include <CTRPluginFramework.hpp>

#include "ScriptEngine/Types/Token.h"
#include "ScriptEngine/Types/Variable.h"
#include "ScriptEngine/Types/TypeInfo.h"
#include "ScriptEngine/Types/Object.h"
#include "ScriptEngine/Types/Node.h"

#include "ScriptEngine/Parser.h"
#include "ScriptEngine/Exceptions.h"

namespace CTRPluginFramework::ScriptEngine {
  
  bool Parser::check() {
    return token->kind != TOK_END;
  }

  void Parser::next() {
    token = token->next;
  }

  bool Parser::eat(std::string_view s) {
    if( token->str == s ) {
      ate = token;
      next();
      return true;
    }

    return false;
  }

  void Parser::expect(std::string_view s) {
    if( !eat(s) ) {
      throw ParseError(token, "expected '" + std::string(s) + "'");
    }
  }

  void Parser::expect_ident() {
    if( token->kind != TOK_IDENT ) {
      throw ParseError(token, "expected identifier");
    }
  }

  Node* Parser::expect_typename() {

    // todo

    return nullptr;
  }

}