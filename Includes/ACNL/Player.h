#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework::ACNL {
  class Player {

  public:
    
    static int WriteItem(u32 item, u16 slot = -1) {
      u32* player_pointer = (u32*)(0xAA914c);
      u32* inv_addrs = (u32*)(player_pointer[0] + 0x6BD0);

      if( slot < 0 ) {
        for( int i = 0; i < 16; i++) {
          if( inv_addrs[i] == 0x7FFE || i == 15 ) {
            inv_addrs[i] = item;
            return i;
          }
        }
      }

      *(u32*)(inv_addrs + slot * 4) = item;
      return int(slot);
    }

    static u32 ReadItem(u16 slot) {
      u32* player_pointer = (u32*)(0xAA914c);
      u32* inv_addrs = (u32*)(player_pointer[0] + 0x6BD0);

      return inv_addrs[slot * 4];
    }

  };
}