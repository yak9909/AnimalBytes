#pragma once

#include "types.h"
#include <vector>

namespace CTRPluginFramework::ScriptEngine {
  enum NodeKind {
    ND_VALUE,
    ND_CALLFUNC,

    ND_ADD,
  };

  struct Token;
  struct Variable;
  struct Node {
    NodeKind  kind;
    Token*    token;
    Node*     lhs;
    Node*     rhs;
    
    std::vector<Node*> list;
    std::vector<Variable> variables;

    static auto _f_() {sizeof(Node);}

    explicit Node(NodeKind kind);
    Node(NodeKind kind, Node* lhs, Node* rhs, Token* token);
  };
}