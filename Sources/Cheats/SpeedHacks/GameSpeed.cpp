#include <CTRPluginFramework.hpp>
#include "Cheats/SpeedHack.h"

namespace CTRPluginFramework::Cheats::SpeedHacks {
  void gamespeed_boost(MenuEntry* entry) {
    static int flag = 1;

    if( Controller::IsKeysPressed(Key::B + Key::DPadUp) ) {
      if( flag ) {
        *(u32*)(0x0054C6E8) = 0xE3E004FF;
        OSD::Notify("Game Speed" << Color::LimeGreen << " Boosted!");
      }
      else {
        *(u32*)(0x0054C6E8) = 0xE59400A0;
        OSD::Notify("Game Speed Reset!");
      }
    }
  }
}