#pragma once
#include <CTRPluginFramework.hpp>

namespace ACNL {
  class Player {
  public:
    
    static int WriteItem(u32 item, u16 slot = -1) {
      u32* inv_addrs = (u32*)((*(u32*)(0xAA914c) + 0x6BD0));

      if( slot < 0 ) {
        for( int i = 0; i < 16; i++) {
          if( inv_addrs[i] == 0x7FFE ) {
            inv_addrs[i] = item;
            return i;
          }

          if( i == 15 ) {
            inv_addrs[i] = item;
            return i;
          }
        }
      }

      *(u32*)(inv_addrs + slot * 4) = item;
      return slot;
    }

    static u32 ReadItem(u16 slot) {
      u32* inv_addrs = (u32*)((*(u32*)(0xAA914c) + 0x6BD0));
      return inv_addrs[slot * 4]
    }

  };
}