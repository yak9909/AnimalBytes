#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>
#include <vector>

#include "Cheats.h"
#include "Helpers.h"

#include "TextEditor.h"

static char const *ABOUT =
    "Animal Bytes: ACNL Plugin\n"
    "\n"
    "Developers:\n"
    "  bomkei (Main Developer)\n"
    "  yak9909 (Cheat codes)\n"
    "  HIDE810 (Debuggings)\n";

/* ---------------------

注意
  以下のアドレスは、AnimalBytes によって予約されているものです
  Process::CheckAddress がこれらに対して false
を返すようになっています

  0x838000 ~ 0x839000

  --------------------- */

namespace CTRPluginFramework {
void PatchProcess(FwkSettings &settings)
{
  __attribute__((packed)) struct patch_table_t {
    u32 addr;
    u32 enable;
    u32 disable;
  };

  static constexpr patch_table_t patchlist[] = {
      // force drop
      {0x59E5DC, 0xEA000004, 0x0A000004},
  };

  for (auto &&[A, E, D] : patchlist)
    *(u32 *)A = E;

  // force drop
  // *(u32 *)0x59E5DC = 0xEA000004;
}

void OnProcessExit(void)
{
}

void InitMenu(PluginMenu &menu)
{
  Cheats::TextToCheats::initialize(menu);
  Cheats::SpeedHacks::initialize();

  Cheats::CodeContext::get_instance()->init();

  menu += new MenuEntry("TextEditor", nullptr, [](MenuEntry *e) {
    static TextEditor editor;

    editor.open();
  });

  menu += Cheats::Movements::make_folder();
  menu += Cheats::SpeedHacks::make_folder();
  menu += Cheats::Items::make_folder();
  menu += Cheats::ItemDrops::make_folder();
}

int main()
{
  PluginMenu menu{"AnimalBytes", 1, 0, 0, ABOUT};
  Logger logger{"plugin.log"};

  menu.SynchronizeWithFrame(true);
  menu.ShowWelcomeMessage(false);

  // Create Menu
  InitMenu(menu);

  OSD::Notify(Color::DodgerBlue << "AnimalBytes Ready!!");

  return menu.Run();
}
}  // namespace CTRPluginFramework
