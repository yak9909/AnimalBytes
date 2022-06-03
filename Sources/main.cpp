#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>
#include <vector>

#include "Cheats.h"
#include "Helpers.h"

namespace CTRPluginFramework {
  static void ToggleTouchscreenForceOn() {
    static u32 original = 0;
    static u32 *patchAddress = nullptr;

    if( patchAddress && original ) {
      *patchAddress = original;
      return;
    }

    static const std::vector<u32> pattern ={
      0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
      0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
      0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
    };

    Result  res;
    Handle  processHandle;
    s64     textTotalSize = 0;
    s64     startAddress = 0;
    u32 *   found;

    if( R_FAILED(svcOpenProcess(&processHandle, 16)) )
      return;

    svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
    svcGetProcessInfo(&startAddress, processHandle, 0x10005);
    if( R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)) )
      goto exit;

    found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

    if( found != nullptr ) {
      original = found[13];
      patchAddress = (u32 *)PA_FROM_VA((found + 13));
      found[13] = 0xE1A00000;
    }

    svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
    svcCloseHandle(processHandle);
  }

  void PatchProcess(FwkSettings &settings) {
    ToggleTouchscreenForceOn();
  }

  void OnProcessExit(void) {
    ToggleTouchscreenForceOn();
  }

  void InitMenu(PluginMenu& menu) {
    Cheats::TextToCheats::initialize(menu);
    Cheats::SpeedHacks::initialize();

    menu += new MenuEntry("test", [] (MenuEntry* e) {
      if( Controller::IsKeyPressed(Key::L) ) {
        InstantMenu_Int menu;

        menu.set_title("numbers");
        menu.set_menu_draw_pos(50, 30);

        for(int i=0;i<100;i++){
          menu.append(i);
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
  }

  int main() {
    PluginMenu menu{ "AnimalBytes", 1, 0, 0, "ACNL Plugin by Yakuruto and bomkei" };

    menu.SynchronizeWithFrame(true);
    menu.ShowWelcomeMessage(false);

    InitMenu(menu);

    OSD::Notify(Color::DodgerBlue << "AnimalBytes Ready!!");

    return menu.Run();
  }
}
