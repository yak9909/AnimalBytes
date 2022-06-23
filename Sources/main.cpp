#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>
#include <vector>

#include "Cheats.h"
#include "Helpers.h"

#include "TextEditor.h"

static char const* ABOUT =
  "Animal Bytes: ACNL Plugin\n"
  "\n"
  "Developers:\n"
  "  bomkei (Main Developer)\n"
  "  yak9909 (Cheat codes)\n"
  "  HIDE810 (Debuggings)\n";

/* ---------------------

注意
  以下のアドレスは、AnimalBytes によって予約されているものです
  Process::CheckAddress がこれらに対して false を返すようになっています

  0x838000 ~ 0x839000

  --------------------- */

namespace CTRPluginFramework {
  void InitHooks();

  void PatchProcess(FwkSettings &settings) {
    // force drop
    *(u32*)0x59E5DC = 0xEA000004;


  }

  void OnProcessExit(void) {
  }

  void InitMenu(PluginMenu& menu) {
    
    Cheats::TextToCheats::initialize(menu);
    Cheats::SpeedHacks::initialize();

    Cheats::CodeContext::get_instance()->init();

    menu += new MenuEntry("test", [] (MenuEntry* e) {
      if( Controller::IsKeyPressed(Key::L) ) {
        InstantMenu_Int menu;

        menu.set_title("numbers");
        menu.set_menu_draw_pos(50, 30);

        for(int i=0;i<100;i++){
          menu.append_item(i);
        }

        long index = menu.open();

        if( index >= 0 ) {
          OSD::Notify(std::to_string(menu.get_items()[index]));
        }
        else {
          OSD::Notify("Canceled!");
        }
      }
    });

    menu += Cheats::Movements::make_folder();
    menu += Cheats::SpeedHacks::make_folder();
    menu += Cheats::Items::make_folder();
    menu += Cheats::ItemDrops::make_folder();
  }

  int main() {
    PluginMenu menu{ "AnimalBytes", 1, 0, 0, ABOUT };
    Logger logger{ "plugin.log" };

    menu.SynchronizeWithFrame(true);
    menu.ShowWelcomeMessage(false);

    // Initialize hooks
    InitHooks();

    // Create Menu
    InitMenu(menu);

    OSD::Notify(Color::DodgerBlue << "AnimalBytes Ready!!");

    return menu.Run();
  }
}
