#include <CTRPluginFramework.hpp>
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "Cheats/TextToCheats.h"
#include "DevUtils/ViewerEx.h"

namespace CTRPluginFramework::Cheats::TextToCheats {
  void initialize(PluginMenu const& menu) {
    ACNL::ChatCommands::init();

    ACNL::ChatCommands::append_func("toggle", toggle_cheat);
    ACNL::ChatCommands::append_func("vx", DevUtils::ViewerEx::cmd_line);

    ACNL::ChatCommands::append_hook(text_to_item);
    ACNL::ChatCommands::append_hook(find_item);

    menu += ACNL::ChatCommands::call_back;
  }


}