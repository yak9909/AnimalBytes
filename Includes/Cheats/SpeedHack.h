#pragma once

namespace CTRPluginFramework::Cheats::SpeedHacks {
  MenuFolder* make_folder();

  void speedhackmenu_routine(MenuEntry* entry);
  void gamespeed_boost(MenuEntry* entry);
}