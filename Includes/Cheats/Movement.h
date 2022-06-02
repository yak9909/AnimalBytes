#pragma once

namespace CTRPluginFramework::Cheats {
  class Movements {
  public:
    static void coord_mod(MenuEntry* entry);

    static MenuFolder* make_folder();
  };
}