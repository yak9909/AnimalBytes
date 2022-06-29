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

  Node* Parser::factor() {

  }

  Node* Parser::mul() {

  }

  Node* Parser::add() {

  }

  Node* Parser::expr() {
    return add();
  }


}