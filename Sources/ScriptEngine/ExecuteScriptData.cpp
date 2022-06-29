#include <string>
#include <vector>
#include <map>
#include <CTRPluginFramework.hpp>

#include "ScriptEngine/Types/Token.h"
#include "ScriptEngine/Types/Variable.h"
#include "ScriptEngine/Types/TypeInfo.h"
#include "ScriptEngine/Types/Object.h"
#include "ScriptEngine/Types/Node.h"
#include "ScriptEngine/Types/IL.h"

#include "ScriptEngine/Lexer.h"
#include "ScriptEngine/ScriptManager.h"

#include "ScriptEngine/Exceptions.h"

namespace CTRPluginFramework::ScriptEngine {
  
  struct Machine {
    Object* reg[8];
    Object* fp;
    Object* sp;
    u32 ip;
    u32 lr;
    u32 pc;
  };

  static std::map<ScriptData*, Machine> machinemap;

  Object* ScriptData::execute() {
    size_t index = 0;

    auto& machine = machinemap[this];


    return nullptr;
  }

}