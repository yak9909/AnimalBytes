#include <CTRPluginFramework.hpp>
#include "ACNL/Game.h"
#include "ACNL/Chat.h"
#include "Cheats.h"

namespace CTRPluginFramework::Cheats::ItemDrops {

  using namespace ACNL;

  // static bool enabled = 0;
  // static u32 item = 0x2001;
  // static int counter = -1;
  // static bool check_item_id = 0;

  // static constexpr int canChangeItemID = 30;

  void auto_drop(MenuEntry* e) {
    auto const ctx = CodeContext::get_instance();
    auto& ctxdrop = ctx->c_autodrop;

    // Enable / Disable
    if( Controller::IsKeysPressed(Hotkeys::AutoDrop) ) {
      ctx->enabled_flags.f_autodrop ^= 1;
    }

    if( !ctx->enabled_flags.f_autodrop )
      return;
    
    u8 wx, wy, u0;

    if( Game::drop_check(&wx, &wy, &u0, 0, 0) ) {
      ctx->c_dropcheats.drop(wx, wy);

      //Game::place_item(0xA, (u32*)(0x955FF4), &ctxdrop.item, &ctxdrop.item, wx, wy, 0, 0, 0, 0, 0);
    }
  }

}
