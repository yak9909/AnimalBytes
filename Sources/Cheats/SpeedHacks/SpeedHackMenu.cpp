#include <CTRPluginFramework.hpp>
#include "Cheats/SpeedHack.h"
#include "Helpers/InstantMenu.h"
#include "Helpers/Strings.h"
#include <map>
#include <sstream>
#include <istream>

namespace CTRPluginFramework::Cheats::SpeedHacks {
  static InstantMenu speedhack_menu;
  static bool initialized = false;

  struct Cheat {
    int flag;
    std::vector<u32> Adresses;
  };
  std::map<std::string, Cheat> speedhack_map;

  void Initialize() {
    speedhack_menu.set_title("SpeedHack Menu");
    speedhack_menu.set_menu_draw_pos(50, 30);

    speedhack_map["Shovel"] = {1, {0x672740, 0x66ED64, 0x669308}};
    speedhack_map["Axe"] = {1, {0x671880, 0x671944, 0x65F624}};
    speedhack_map["Hikkonuku"] = {1, {0x67AD1C}};
    speedhack_map["Pickup"] = {1, {0x65FA28}};

    for(auto itr = speedhack_map.begin(); itr != speedhack_map.end(); ++itr) {
      speedhack_menu.append(itr->first << Color::Red << " OFF");
    }
    initialized = true;
  }

  void speedhackmenu_routine(MenuEntry* entry) {
    u32 keys = Controller::GetKeysDown();

    if( !initialized ) {
      Initialize();
    }

    if( keys & Key::ZR ) {
      long index = speedhack_menu.open();

      if( index >= 0 ) {
        std::string speed_name = trim_string(speedhack_menu.get_items()[index], ' ')[0];
        for( int i = 0; i < (sizeof(speedhack_map[speed_name].Adresses) / sizeof(u32) / 3); i++ ) {
          *(u32*)(speedhack_map[speed_name].Adresses[i*3]) = (u32)(1.0 + (speedhack_map[speed_name].flag * 30));
        }

        if( speedhack_map[speed_name].flag ) {
          OSD::Notify(Color::Yellow << speed_name << Color::LimeGreen << " Speed Boosted!");
          speedhack_menu.set_item(index, speed_name << " " << Color::LimeGreen << "ON");
        }
        else {
          OSD::Notify(Color::Yellow << speed_name << Color::White << " Speed Reset!");
          speedhack_menu.set_item(index, speed_name << " " << Color::Red << "OFF");
        }

        speedhack_map[speed_name].flag ^= 1;
      }
    }
  }

}