#include <CTRPluginFramework.hpp>
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "Cheats/TextToCheats.h"

namespace CTRPluginFramework::Cheats::TextToCheats {
  void toggle_cheat(Args const& args) {
    if( args.empty() ) {
      return;
    }

    auto& name = args[0];

    OSD::Notify(name);
  }

}