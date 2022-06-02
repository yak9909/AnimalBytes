#include <CTRPluginFramework.hpp>
#include "Cheats/Movement.h"

namespace CTRPluginFramework::Cheats {
  void Movements::coord_mod(MenuEntry* entry) {
    u32 keys = Controller::GetKeysDown();

    float* coord = (float*)(0x33099E50);
    constexpr float speed = 3;

    if( keys & Key::DPadUp ) coord[2] -= speed;
    if( keys & Key::DPadDown ) coord[2] += speed;
    if( keys & Key::DPadLeft ) coord[0] -= speed;
    if( keys & Key::DPadRight ) coord[0] += speed;
  }
}