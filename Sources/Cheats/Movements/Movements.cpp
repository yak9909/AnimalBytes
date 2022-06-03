#include <CTRPluginFramework.hpp>
#include "Cheats/Movement.h"

namespace CTRPluginFramework::Cheats::Movements {
  MenuFolder* make_folder() {
    MenuFolder* folder = new MenuFolder("Movements", "", {
      new MenuEntry("座標移動", coord_mod),
      new MenuEntry("壁抜け", walk_everywhere)
    });

    return folder;
  }
}