#pragma once

namespace CTRPluginFramework {
  namespace ACNL {
    namespace Sys {
      u16* copy32_2fc878(u16* dest, u16* src);
    };

    namespace Game {
      std::pair<u16*, u32> get_item_name_addr(u16 item);
      bool get_item_name(u16 item, std::string& out);

      u32 get_current_map();
      u32* get_item_at_world_coords(u32 map_ptr, u8 wx, u8 wy, u8 u0);
      u8 get_online_player_index();

      int get_active_drop_index(u8 wx, u8 wy, u8 u0);
      bool drop_check(u8* wx_out, u8* wy_out, u8* u0_out, bool disallow_concrete, u8 u1);
      bool place_item(u8 type, u32* item_to_replace, u32* item_to_place, u32* item_to_show, u8 wx, u8 wy, bool is_inside, u8 u0, u8 u1, u8 u2, u8 u3);
      bool place_item_wrap(u8 type, u32 item, u8 wx, u8 wy);

      void particle(u16 id, float* coords, u32 u0, u32 u1);
    }
  }
}