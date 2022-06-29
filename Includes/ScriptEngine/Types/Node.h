#pragma once

#include "types.h"
#include <vector>

namespace CTRPluginFramework::ScriptEngine {
  enum NodeKind : u16 {
    ND_VALUE,
    ND_VARIABLE,
    ND_CALLFUNC,

    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_MOD,
  };

  struct Token;
  struct Variable;
  struct Node {
    NodeKind  kind;
    Token*    token;
    Node*     lhs;
    Node*     rhs;
    Object*   obj;
    
    std::vector<Node*> list;
    std::vector<Variable> variables;

    static auto _f_() {sizeof(Node);}

    explicit Node(NodeKind kind);
    Node(NodeKind kind, Node* lhs, Node* rhs, Token* token);
  };
}