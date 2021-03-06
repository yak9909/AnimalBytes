#pragma once

#include <CTRPluginFramework.hpp>
#include "Cheats/Movement.h"
#include "Cheats/SpeedHack.h"
#include "Cheats/Item.h"
#include "Cheats/ItemDrops.h"
#include "Cheats/TextToCheats.h"
#include "Cheats/CodeContext.h"

namespace CTRPluginFramework::Cheats {
  namespace Hotkeys {
    constexpr u32
      AutoDrop       = Key::B | Key::DPadUp,
      ItemChanger    = Key::R | Key::DPadUp
      ;
  };
}