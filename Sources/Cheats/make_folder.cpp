#include <CTRPluginFramework.hpp>
#include "Cheats/Movement.h"
#include "Cheats/SpeedHack.h"

namespace CTRPluginFramework::Cheats {
  namespace Movements {
    MenuFolder* make_folder() {
      MenuFolder* folder = new MenuFolder("Movements", "", {
        new MenuEntry("座標移動", coord_mod, "Aぼたんとじゅうじ"),
        new MenuEntry("座標移動(グリッド)", coord_grid, "Aぼたんとじゅうじ"),
        new MenuEntry("座標移動 スピード変更", nullptr, change_speed),
        new MenuEntry("壁抜け", walk_everywhere, "Lぼたんとうえ")
      });

      return folder;
    }
  }

  namespace SpeedHacks {
    MenuFolder* make_folder() {
      MenuFolder* folder = new MenuFolder("SpeedHacks", "", {
        new MenuEntry("スピードハックメニュー", speedhackmenu_routine, "ZR"),
        new MenuEntry("ゲームスピード上昇", gamespeed_boost, "Bぼたんとうえ")
      });

      return folder;
    }
  }
}