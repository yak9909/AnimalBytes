#pragma once

namespace CTRPluginFramework::ScriptEngine {
  struct Object {
    TypeInfo  type;
    u32 ref_count;

    union {
      int v_int;
      float v_float;
      char v_char;
      bool v_bool;

    };

    
  };
}