#include <CTRPluginFramework.hpp>
#include "ACNL/Game.h"
#include "ACNL/Chat.h"
#include "Cheats.h"

namespace CTRPluginFramework::Cheats::ItemDrops {

  using namespace ACNL;

  namespace {
    int key_held_tick = 0;

    constexpr int canChangeItemID = 30;
    constexpr int notify_showing_time = 60;
  }

  static bool cb(Screen const& screen) {
    static int notify_tick = 0;

    if( !screen.IsTop ) {
      return false;
    }

    u32 dy = 10;
    bool b = 0; // drawed

    auto ctx = CodeContext::get_instance();

    // view item
    if( key_held_tick > 0 ) {
      auto&& item = ctx->c_dropcheats.item;

      screen.Draw(Utils::Format((item & (0xFFFF << 16)) ? "%08X" : "%04X", item), 10, dy);
      dy += 10;
      b = 1;
    }

    // change item
    if( key_held_tick >= canChangeItemID ) {
      screen.Draw("change item id ...", 10, dy);
      dy += 10;
      b = 1;
    }

    return b;
  }

  void item_changer(MenuEntry* e) {
    if( e->WasJustActivated() ) {
      key_held_tick = 0;
      OSD::Run(cb);
    }
    else if( !e->IsActivated() ) {
      OSD::Stop(cb);
    }

    if( Controller::IsKeysDown(Hotkeys::ItemChanger) ) {
      key_held_tick++;
    }
    else if( key_held_tick >= canChangeItemID ) {
      Keyboard("change item id to drop").Open(CodeContext::get_instance()->c_dropcheats.item);
      key_held_tick = 0;
    }
    else if( key_held_tick > 0 ) {
      key_held_tick = 0;
    }
  }

}
