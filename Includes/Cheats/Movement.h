#pragma once

namespace CTRPluginFramework::Cheats::Movements {
  MenuFolder* make_folder();

  void coord_mod(MenuEntry* entry);
  void walk_everywhere(MenuEntry* entry);
}