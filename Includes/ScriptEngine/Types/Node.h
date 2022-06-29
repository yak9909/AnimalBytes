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
  struct PACKED Node {
    NodeKind  kind;
    Token*    token;
    Node*     lhs;
    Node*     rhs;
    
    std::vector<Node*> list;

    static auto _f_() {sizeof(Node);}
  };
}