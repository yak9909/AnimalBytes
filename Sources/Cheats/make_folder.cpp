#include <CTRPluginFramework.hpp>
#include "Cheats.h"
#include "Unicode.h"

namespace CTRPluginFramework::Cheats {
  static MenuEntry* EnableEntry(MenuEntry* e) {
    e->Enable();
    return e;
  }

  namespace Movements {
    MenuFolder* make_folder() {
      MenuFolder* folder = new MenuFolder("Movements", "", {
        new MenuEntry("座標移動 " FONT_A " + " FONT_D, coord_mod),
        new MenuEntry("座標移動(グリッド) " FONT_A " + " FONT_D, coord_grid),
        new MenuEntry("座標移動 スピード変更", nullptr, change_speed),
        new MenuEntry("壁抜け " FONT_L " + " FONT_DU, walk_everywhere)
      });

      return folder;
    }
  }

  namespace SpeedHacks {
    MenuFolder* make_folder() {
      MenuFolder* folder = new MenuFolder("SpeedHacks", "", {
        new MenuEntry("スピードハックメニュー " FONT_B " + " FONT_DD, speedhackmenu),
        new MenuEntry("ゲームスピード上昇 " FONT_B " + " FONT_DU, gamespeed_boost)
      });

      return folder;
    }
  }

  namespace Items {
    MenuFolder* make_folder() {
      MenuFolder* folder = new MenuFolder("Items", "", {
        new MenuEntry("ポケットアイテム " FONT_L " + " FONT_B, pocket_item)
      });

      return folder;
    }
  }

  namespace ItemDrops {
    MenuFolder* make_folder() {
      auto folder = new MenuFolder("Item Drops", "", {
        EnableEntry(new MenuEntry("アイテム変更 " FONT_R " + " FONT_DU, item_changer)),
        new MenuEntry("自動ドロップ " FONT_B " + " FONT_DU, auto_drop)
      });

      return folder;
    }
  }
}