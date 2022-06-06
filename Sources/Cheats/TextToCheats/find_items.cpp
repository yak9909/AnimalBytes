#include <CTRPluginFramework.hpp>
#include "ACNL/types.h"
#include "ACNL/Game.h"
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "ACNL/Player.h"
#include "Cheats/TextToCheats.h"
#include "Helpers.h"

namespace CTRPluginFramework::Cheats::TextToCheats {

  bool find_item(std::string const& text) {

    File file("items.txt", File::READ);
    LineReader reader(file);

    std::string line;
    std::vector<u16> hit_ids;
    std::vector<std::string> hit_names;

    if( !file.IsOpen() ) {
      ACNL::Chat::write_text("cannot open items.txt");
      return true;
    }

    while( reader(line) ) {
      auto&& trimmed = trim_string(line, ' ');

      if( trimmed[2].find(text) != std::string::npos ) {
        hit_ids.emplace_back(std::stoi(trimmed[0], nullptr, 16));
        hit_names.emplace_back(trimmed[1]);
      }
    }

    if( hit_ids.empty() ) {
      ACNL::Chat::write_text("アイテムが見つかりません。");
      return true;
    }

    Keyboard kbd{ hit_names };
    int index = kbd.Open();

    if( index >= 0 ) {
      ACNL::Chat::write_text(Utils::Format("ポケット0 = %04X", hit_ids[index]));
      return true;
    }

    return false;
  }

}