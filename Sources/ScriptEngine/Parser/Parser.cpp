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
  
  static std::vector<Parser*> _g_parser_instances;

  Parser::Parser(Token* token)
    : token(token),
      ate(nullptr)
  {
    _g_parser_instances.emplace_back(this);
  }

  Parser::~Parser() {
    _g_parser_instances.pop_back();
  }

  Node* Parser::parse() {
    return expr();
  }

  Parser* Parser::get_instance() {
    return *_g_parser_instances.rbegin();
  }

}