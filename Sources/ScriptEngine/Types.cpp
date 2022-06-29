#include <CTRPluginFramework.hpp>

#include "ScriptEngine/Types/Token.h"
#include "ScriptEngine/Types/Variable.h"
#include "ScriptEngine/Types/TypeInfo.h"
#include "ScriptEngine/Types/Object.h"
#include "ScriptEngine/Types/Node.h"
#include "ScriptEngine/Types/IL.h"

namespace CTRPluginFramework::ScriptEngine {
  Token::Token(TokenKind kind)
    : kind(kind),
      str({}),
      next(nullptr),
      pos(0)
  {
  }
  
  Token::Token(TokenKind kind, Token* prev, size_t pos)
    : kind(kind),
      str({}),
      next(nullptr),
      pos(pos)
  {
    if( prev ) prev->next = this;
  }

  Variable::Variable(std::string_view const& name)
    : name(name),
      value(nullptr)
  {
  }

  Node::Node(NodeKind kind)
    : kind(kind),
      token(nullptr),
      lhs(nullptr),
      rhs(nullptr)
  {
  }

  Node::Node(NodeKind kind, Node* lhs, Node* rhs, Token* token)
    : kind(kind),
      token(token),
      lhs(lhs),
      rhs(rhs)
  {
  }

}