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

    static auto adjustStr = [] (std::u16string& s) -> void {
      for( auto& c : s ) {
        if( c >= 0x30A1 && c <= 0x30F3 )
          c -= 0x60;
        else if( c >= 0x61 && c <= 0x7A )
          c -= 0x20;
      }
    };

    u16 buf[0x100] { 0 };

    utf8_to_utf16(buf, (u8*)text.c_str(), sizeof(buf));

    std::u16string find = (char16_t*)buf;

    std::vector<u16> hit_id;
    std::vector<std::string> hit_names;

    adjustStr(find);

    for( u16 id = 0x2000; id <= 0x372B; id++ ) {
      auto [name_addr, len] = ACNL::Game::get_item_name_addr(id);

      std::u16string name{ (char16_t*)name_addr, len };

      adjustStr(name);

      if( name.find(find) != std::string::npos ) {
        std::string str;
        Process::ReadString((u32)name_addr, str, len * 2, StringFormat::Utf16);

        hit_id.emplace_back(id);
        hit_names.emplace_back(str);
      }
    }

    if( hit_id.empty() ) {
      ACNL::Chat::write_text("アイテムが見つかりません。");
      return true;
    }

    Keyboard kbd{ hit_names };
    int index = kbd.Open();

    if( index >= 0 ) {
      ACNL::Player::WriteItem(hit_id[index], 0);
      ACNL::Chat::write_text(Utils::Format("ポケット0 = %04X", hit_id[index]));
      return true;
    }

    return false;
  }

}