#pragma once

namespace CTRPluginFramework::ACNL::Game {
  std::pair<u16*, u32> get_item_name_addr(u16 item);
  bool get_item_name(u16 item, std::string& out);
}