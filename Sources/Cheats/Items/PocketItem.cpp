#include <CTRPluginFramework.hpp>
#include "Cheats/Item.h"
#include "ACNL/Player.h"

namespace CTRPluginFramework::Cheats::Items {
  void pocket_item(MenuEntry* entry) {
    u32 keys = Controller::GetKeysDown();
    Keyboard kbd("取得するアイテムIDを入力");
    u32 itemid;

    if( Controller::IsKeysPressed(Key::L + Key::B) ) {
      int result = kbd.Open(itemid);
      if( result >= 0 ) {
        int inv_index = ACNL::Player::WriteItem(itemid);
        OSD::Notify("Pocket Item: " << Color::Yellow << "Index " << Color::Green << std::to_string(inv_index));
      }
    }
  }
}