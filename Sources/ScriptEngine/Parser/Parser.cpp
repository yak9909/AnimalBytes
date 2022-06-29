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
  
  Parser::Parser(Token* token)
    : token(token),
      ate(nullptr)
  {
  }

  Node* Parser::parse() {
    return expr();
  }

}