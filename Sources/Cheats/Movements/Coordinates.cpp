#include <CTRPluginFramework.hpp>
#include "Cheats/Movement.h"
#include <math.h>

namespace CTRPluginFramework::Cheats::Movements {
static float speed = 6;

  void coord_mod(MenuEntry* entry) {
    u32 keys = Controller::GetKeysDown();

    float* coord = (float*)(add12c(0x33099E50));
    float add_speed = 0;

    if( keys & Key::L ) {
      add_speed = speed * 1.8;
    }

    if( keys & Key::A ) {
      if( keys & Key::DPadUp ) coord[2] -= speed + add_speed;
      if( keys & Key::DPadDown ) coord[2] += speed + add_speed;
      if( keys & Key::DPadLeft ) coord[0] -= speed + add_speed;
      if( keys & Key::DPadRight ) coord[0] += speed + add_speed;
    }
  }

  void coord_grid(MenuEntry* entry) {
    u32 keys = Controller::GetKeysDown();

    float* coord = (float*)(add12c(0x33099E50));
    u32* grid = (u32*)(0x3309A2B8);

    int max_tick = std::max(0, (int)(25 - round(speed * 1.8)));
    static int tick = 0;

    if( *(u32*)(0x33099F84) != -1 ) {
      return;
    }

    if( keys & Key::A ) {
      if( (keys & Key::A) && (keys & (Key::DPadUp | Key::DPadDown | Key::DPadLeft | Key::DPadRight)) ) {
        tick--;

        if( keys & Key::L ) {
          tick -= 3;
        }

        if( tick < 0 ) {
          coord[0] = 528 + ( (grid[0] - 0x10) * 32 );
          coord[2] = 528 + ( (grid[1] - 0x10) * 32 );

          if( keys & Key::DPadUp ) coord[2] -= 32;
          if( keys & Key::DPadDown ) coord[2] += 32;
          if( keys & Key::DPadLeft ) coord[0] -= 32;
          if( keys & Key::DPadRight ) coord[0] += 32;

          tick = max_tick;
        }
      }
      else {
        tick = 0;
      }
    }
  }

  void change_speed(MenuEntry* entry) {
    float temp_speed = speed;

    Keyboard spd("移動速度を指定してください\n現在: " << std::to_string(speed) << "\nデフォルト: 6");
    spd.Open(temp_speed, speed);

    if( temp_speed != -1 ) {
      speed = temp_speed;
    }
  }
}