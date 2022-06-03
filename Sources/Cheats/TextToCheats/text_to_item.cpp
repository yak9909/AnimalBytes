#include <CTRPluginFramework.hpp>
#include "ACNL/types.h"
#include "ACNL/Game.h"
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "Cheats/TextToCheats.h"

namespace CTRPluginFramework::Cheats::TextToCheats {
  static u16 str_to_hex(std::string const& s) {
    #define ctox(c) ((u8)((c > '9') ? (c <= 'F' ? c - 'A' : c - 'a') : (c - '0')))

    u16 v = 0, i = 1;

    for( int i = 3; i >= 0; i-- ) {
      v += ctox(s[i]) * i;
      i *= 0x10;
    }

    return v;
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

    ACNL::ItemInfo item;
    u16 id = str_to_hex(text);

    if( !ACNL::Game::get_item_name(id, item) ) {
      ACNL::Chat::write_text(Utils::Format("アイテムが見つかりません: %04X", id));
      return false;
    }

    

    ACNL::Chat::write_text("ポケット 1 = " + item.first);
    return true;
  }

}