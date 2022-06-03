#pragma once

#include "types.h"

namespace CTRPluginFramework::DevUtils {
  class FunctionCaller {

    u32 addr;
    std::vector<u32> args;

  public:  
    static void game_func(MenuEntry* entry);
    static void menu_func(MenuEntry* entry);

  };
}