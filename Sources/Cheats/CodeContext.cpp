#include <CTRPluginFramework.hpp>
#include "Cheats/CodeContext.h"
#include "ACNL/Game.h"

namespace CTRPluginFramework::Cheats {
  static CodeContext* g_cdctx_instance;

  bool CodeContext::DropCheats::drop(u8 wx, u8 wy) {
    return
      ACNL::Game::place_item(
        this->type, (u32*)0x955FF4, &this->item, &this->item,
        wx, wy, 0, 0, 0, 0, 0
      );
  }

  void CodeContext::init() {
    memset(this, 0, sizeof(*this));
    
    this->c_dropcheats.item = 0x2001;
    this->c_dropcheats.type = 0xA;
  }

  CodeContext* CodeContext::get_instance() {
    static_assert(
      sizeof(CodeContext) < 0x1000,
      "Size of CodeContext is too big to place to 0x838000, must less than 0x1000."
    );

    return reinterpret_cast<CodeContext*>(0x838000);

    // if( !g_cdctx_instance ) {
    //   g_cdctx_instance = new CodeContext;
    // }

    // return g_cdctx_instance;
  }

  CodeContext::CodeContext() {
    
  }
}