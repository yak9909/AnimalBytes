#pragma once

#include <string>
#include <vector>

namespace CTRPluginFramework::Cheats::TextToCheats {
  using Args = std::vector<std::string>;

  void initialize();

  // toggle name [true / false]
  void toggle_cheat(Args const& args);
}