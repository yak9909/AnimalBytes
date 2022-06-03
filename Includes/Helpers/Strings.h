#pragma once

#include <string>
#include <vector>
#include "types.h"

namespace CTRPluginFramework {
  std::string Hex(u64 x, int size);
  std::string Hex(float x);
  std::string Hex(double x);

  std::vector<std::string> trim_string(std::string const& str, char c);
}