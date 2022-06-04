#include <CTRPluginFramework.hpp>
#include "ACNL/types.h"
#include "ACNL/Game.h"
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "ACNL/Player.h"
#include "Cheats/TextToCheats.h"
#include "Helpers.h"

namespace CTRPluginFramework::Cheats::TextToCheats {
  static u16 str_to_hex(std::string const& s) {
    #define ctox(c) ((u8)((c > '9') ? 0xA + (c <= 'F' ? c - 'A' : c - 'a') : (c - '0')))

    u16 ret = 0, v = 1;

    for( int i = 3; i >= 0; i-- ) {
      ret += ctox(s[i]) * v;
      v *= 0x10;
    }

    return ret;
  }

  bool text_to_item(std::string const& text) {
    if( text.length() != 4 ) {
      return false;
    }

    for( auto&& c : text ) {
      if( !isdigit(c) && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F') ) {
        return false;
      }
    }

    u32 id = str_to_hex(text);
    std::string name;

    if( !ACNL::Game::get_item_name(id, name) ) {
      ACNL::Chat::write_text(Utils::Format("アイテムが見つかりません: %04X", id));
    }
    else {
      ACNL::Player::WriteItem(id, 0);
      ACNL::Chat::write_text("ポケット 0 =" + name);
    }

    return true;
  }

}