#pragma once

namespace CTRPluginFramework::ScriptEngine {
  enum TypeKind {
    TYPE_INT,
    TYPE_NONE
  };

  struct TypeInfo {
    TypeKind  kind;
    std::string_view name;
    
  };
}