#include <CTRPluginFramework.hpp>
#include "Cheats/Movement.h"

namespace CTRPluginFramework::Cheats::Movements {
  void walk_everywhere(MenuEntry* entry) {
    u32 keys = Controller::GetKeysPressed();
    static int flag = 1;

    u32 table[] = {
      0x0064EEF4, 0xEA000094, 0x0A000094,
      0x0064EF0C, 0xEA000052, 0x0A000052,
      0x0064F070, 0xEA000001, 0x0A000001,
      0x0064F0E8, 0xEA000014, 0xDA000014,
      0x0064F19C, 0xE1A00000, 0xED841A05,
      0x0064F1B4, 0xE1A00000, 0xED840A07,
      0x0064F1B8, 0xEA000026, 0x0A000026,
      0x0064F1E4, 0xEA000065, 0x0A000065
    };

    if( keys & Key::L && keys & Key::DPadUp ) {
      flag ^= 1;

      for( int i = 0; i < (sizeof(table) / sizeof(u32)) * 3; i++ ) {
        *(u32*)(table[i*3]) = table[(i*3) + (flag + 1)];
      }
    }
  }
}