#include <CTRPluginFramework.hpp>
#include "Cheats/ItemDrops.h"
#include "ACNL/Game.h"
#include "ACNL/Chat.h"

namespace CTRPluginFramework::Cheats::ItemDrops {

  using namespace ACNL;

  static bool enabled = 0;
  static u32 item = 0x2001;
  static int counter = -1;
  static bool check_item_id = 0;

  static constexpr int canChangeItemID = 30;

  static bool cb(Screen const& screen) {
    static int notify_tick = 0;
    #define  NOTIFY_TIME  60

    if( !screen.IsTop ) {
      return false;
    }

    u32 dy = 10;
    bool b = 0;

    if( check_item_id ) {
      screen.Draw(Utils::Format((item & (0xFFFF << 16)) ? "%08X" : "%04X", item), 10, dy, Color::White, Color::Blue);
      dy += 10;
      b = 1;
    }

    if( counter >= canChangeItemID ) {
      screen.Draw("autodrop: change item id ...", 10, dy, Color::White, Color::Blue);
      dy += 10;
      b = 1;
    }

    return b;
  }

  void auto_drop(MenuEntry* e) {
    if( e->WasJustActivated() ) {
      OSD::Run(cb);
    }
    else if( !e->IsActivated() ) {
      OSD::Stop(cb);
    }

    if( Controller::IsKeysDown(Key::B | Key::DPadUp) ) {
      counter++;
    }
    else if( counter >= 30 ) {
      Keyboard("change item to drop").Open(item);
      counter = -1;
    }
    else if( counter >= 0 ) {
      enabled ^= 1;
      counter = -1;
    }

    // check item id
    if( !Chat::is_opened() && Controller::IsKeysDown(Key::B | Key::R) ) {
      check_item_id = 1;
    }
    else if( check_item_id ) {
      check_item_id = 0;
    }

    if( !enabled )
      return;
    
    u8 wx, wy, u0;

    if( Game::drop_check(&wx, &wy, &u0, 0, 0) ) {
      Game::place_item(0xA, (u32*)(0x955FF4), &item, &item, wx, wy, 0, 0, 0, 0, 0);
    }
  }

}