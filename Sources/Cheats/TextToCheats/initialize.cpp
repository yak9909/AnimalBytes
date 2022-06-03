#include <CTRPluginFramework.hpp>
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "Cheats/TextToCheats.h"

namespace CTRPluginFramework::Cheats::TextToCheats {
  void initialize() {
    ACNL::ChatCommands::init();

    ACNL::ChatCommands::append_func("toggle", toggle_cheat);

    ACNL::ChatCommands::run();
  }


}