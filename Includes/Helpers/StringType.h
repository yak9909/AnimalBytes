#pragma once

#include <string>

namespace CTRPluginFramework {
  enum class StringType {
    Integer,
    Hex,
    Alphabets,
    Float,
    Space,
    Empty,
    Other
  };

  StringType get_strtype(std::string const& str);
}