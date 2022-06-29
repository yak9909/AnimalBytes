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

    

    auto node = new Node(ND_VALUE);
    node->token = token;

    switch( token->kind ) {
      case TOK_INT: {
        node->obj = new Object;
        node->obj->type = TYPE_INT;

        next();
        return node;
      }
    }

    throw ParseError(token, "syntax error");
  }

  Node* Parser::mul() {
    auto x = factor();
    
    while( check() ) {
      if( eat("*") ) x = new Node(ND_MUL, x, factor(), ate);
      else if( eat("/") ) x = new Node(ND_DIV, x, factor(), ate);
      else break;
    }

    return x;
  }

  Node* Parser::add() {
    auto x = mul();
    
    while( check() ) {
      if( eat("+") ) x = new Node(ND_ADD, x, mul(), ate);
      else if( eat("-") ) x = new Node(ND_SUB, x, mul(), ate);
      else break;
    }

    return x;
  }

  Node* Parser::expr() {
    return add();
  }


}