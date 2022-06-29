#pragma once

#include "types.h"

namespace CTRPluginFramework::ScriptEngine {
  enum ILOperatorKind : u8 {
    IL_MOV,
    IL_MOVI,

    // expr
    IL_ADD,
    IL_ADDI,
    
    // load / store
    IL_LDR,
    IL_STR,
    IL_PUSH,
    IL_POP,

    // branches
    IL_JUMP,
    IL_CALL,
    IL_SYSCALL,
  };

  struct Object;
  struct PACKED ILOperator {
    ILOperatorKind   kind;
    u8    rdest;
    u8    rsrc;
    u32   addr;
    Object* obj;

    explicit ILOperator(ILOperatorKind kind, u8 ra, u8 rb, Object* obj = nullptr)
      : kind(kind),
        rdest(ra),
        rsrc(rb),
        addr(0),
        obj(obj)
    {
    }
  };
}