#pragma once

#include <string>
#include <vector>

namespace CTRPluginFramework::Cheats::TextToCheats {
  using Args = std::vector<std::string>;

  void initialize(PluginMenu const& menu);

  // get item from id
  bool text_to_item(std::string const& text);

  // toggle name [true / false]
  void toggle_cheat(Args const& args);
}