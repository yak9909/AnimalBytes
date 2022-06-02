#include <CTRPluginFramework.hpp>
#include "Cheats/Movement.h"

namespace CTRPluginFramework::Cheats {
  namespace Movements {
    MenuFolder* make_folder() {
      MenuFolder* folder = new MenuFolder("Movements", "", {
        new MenuEntry("Coordinates Modifier", coord_mod)
      });

      return folder;
    }
  }
}