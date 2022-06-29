#include <CTRPluginFramework.hpp>

#include "ScriptEngine/Types/Token.h"
#include "ScriptEngine/Types/Variable.h"
#include "ScriptEngine/Types/TypeInfo.h"
#include "ScriptEngine/Types/Object.h"
#include "ScriptEngine/Types/Node.h"
#include "ScriptEngine/Types/IL.h"

#include "ScriptEngine/Exceptions.h"
#include "ScriptEngine/Parser.h"

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

  TypeInfo::TypeInfo(TypeKind kind)
    : kind(kind)
  {
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
      rhs(nullptr),
      obj(nullptr)
  {
    auto parser = Parser::get_instance();
    
    if( !parser ) {
      throw FailedToConstructNode(this);
    }

    parser->_allocated_nodes.emplace_back(this);
  }

  Node::Node(NodeKind kind, Node* lhs, Node* rhs, Token* token)
    : kind(kind),
      token(token),
      lhs(lhs),
      rhs(rhs),
      obj(nullptr)
  {
    auto parser = Parser::get_instance();
    
    if( !parser ) {
      throw FailedToConstructNode(this);
    }

    parser->_allocated_nodes.emplace_back(this);
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