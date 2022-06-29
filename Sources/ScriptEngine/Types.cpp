#include <CTRPluginFramework.hpp>

#include "ScriptEngine/Types/Token.h"
#include "ScriptEngine/Types/Variable.h"
#include "ScriptEngine/Types/TypeInfo.h"
#include "ScriptEngine/Types/Object.h"
#include "ScriptEngine/Types/Node.h"
#include "ScriptEngine/Types/IL.h"

#include "ScriptEngine/Exceptions.h"

namespace CTRPluginFramework::ScriptEngine {
  Token::Token(TokenKind kind)
    : kind(kind),
      next(nullptr),
      pos(0)
  {
  }
  
  Token::Token(TokenKind kind, Token* prev, size_t pos)
    : kind(kind),
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

  ParseError::ParseError(size_t pos, std::string const& msg)
    : msg(msg)
  {
    this->errpos = pos;
    
  }

  ParseError::ParseError(Token* token, std::string const& msg)
    : msg(msg)
  {
    this->errpos = token->pos;
    
  }

  ParseError::ParseError(Node* node, std::string const& msg)
    : msg(msg)
  {
    this->errpos = node->token->pos;
  }
      
  char const* ParseError::what() const noexcept {
    return (Utils::Format("pos=%zu: ", errpos) + msg).c_str();
  }
}