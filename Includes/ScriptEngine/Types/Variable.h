#pragma once

#include <string>

namespace CTRPluginFramework::ScriptEngine {
  struct Object;
  struct Variable {
    std::string_view const& name;
    Object* value;

    Variable(std::string_view const& name);
  };
}