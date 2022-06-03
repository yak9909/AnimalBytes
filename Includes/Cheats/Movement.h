#pragma once
#define	add12c(addr) (addr + ( *(u32*)(0x33099F84) != -1 ) * 0x12c)

namespace CTRPluginFramework::Cheats::Movements {
  MenuFolder* make_folder();

  void coord_mod(MenuEntry* entry);
  void coord_grid(MenuEntry* entry);
  void change_speed(MenuEntry* entry);
  void walk_everywhere(MenuEntry* entry);
}