#include <string>
#include <vector>
#include <CTRPluginFramework.hpp>
#include "DevUtils/FunctionCaller.h"

namespace CTRPluginFramework::DevUtils {
  struct FunctionCaller {
    u32 address;
    std::vector<u32> args;
  };

  void game_func(MenuEntry* entry) {

  }

  void menu_func(MenuEntry* entry) {

  }
}