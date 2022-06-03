#pragma once

#include <string>
#include <vector>

namespace CTRPluginFramework::Cheats::TextToCheats {
  using Args = std::vector<std::string>;

  void initialize(PluginMenu const& menu);

  // toggle name [true / false]
  void toggle_cheat(Args const& args);
}