#pragma once

namespace CTRPluginFramework::Cheats::SpeedHacks {
  MenuFolder* make_folder();

  void initialize();

  void speedhackmenu(MenuEntry* entry);
  
  void gamespeed_boost(MenuEntry* entry);
}