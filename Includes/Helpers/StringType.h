#pragma once

#include <string>

namespace CTRPluginFramework {
  enum class StringType {
    Integer,
    Float,
    Char,
    Space,
    Empty,
    Other
  };

  StringType get_strtype(std::string const& str);
}