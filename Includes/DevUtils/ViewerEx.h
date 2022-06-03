#pragma once

#include "types.h"

namespace CTRPluginFramework::DevUtils {

  class ViewerEx {

  public:

    static void gamefunc(MenuEntry* entry);
    static void menufunc(MenuEntry* entry);

    static void cmd_line(std::vector<std::string> const& args);

  };

}