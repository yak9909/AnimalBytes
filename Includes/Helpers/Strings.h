#pragma once

#include <string>
#include <vector>
#include "types.h"

namespace CTRPluginFramework {
  std::string Hex(u8 x);
  std::string Hex(u16 x);
  std::string Hex(u32 x);
  std::string Hex(u64 x);
  std::string Hex(float x);
  std::string Hex(double x);

  std::vector<std::string> trim_string(std::string const& str, char c);
}