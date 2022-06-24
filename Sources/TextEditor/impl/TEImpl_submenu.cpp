#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"

namespace CTRPluginFramework {
  static std::vector<char const*> entries = {
    "Open file",
    "Create a file",
    "Save",
    "Save as ...",
  };

  TextEditorImpl::SubmenuEntry::SubmenuEntry(std::string const& name, TextEditor::EventFuncPointer func)
    : name(name),
      func(func)
  {
  }

  void TextEditorImpl::submenu_draw(Screen const& screen) {
    constexpr int menu_width = 160;

    int x = 400 - menu_width;

    // background
    screen.DrawRect(x, 0, menu_width, 240, submenu_background);
    screen.DrawRect(x, 0, menu_width, 240, submenu_background_box, false);

    // entries
    {
      int begin = std::max<int>(0, submenu_index - 10);
      int end = std::min<int>(entries.size(), begin + 24);
      u32 dy = 4;

      static auto const draw_entry_name = [&] (std::string const& name) -> u32 {
        return screen.Draw(
          name, x + 4, dy,
          begin == submenu_index ? Color::Black : Color::White,
          begin == submenu_index ? Color::White : submenu_background
        );
      };

      // built-in
      for( ; begin < end; begin++, dy += 10 ) {
        auto const entry = entries[begin];

        draw_entry_name(entry);
      }

      // user defined entries
      if( begin < end && !submenu_user_entries.empty() ) {
        end = std::min<int>(entries.size() + submenu_user_entries.size(), begin + 24);

        for( ; begin < end; begin++, dy += 10 ) {
          auto const& entry = submenu_user_entries[begin];

          draw_entry_name(entry.name);
        }
      }
    }


  }

  void TextEditorImpl::submenu_update() {
    static u32 tick = 0;
    static constexpr int mvCursor_WaitToRepeat  = 300;
    static constexpr int mvCursor_RepeatTick    = 100;
    static constexpr int mvCursor_RepeatReset   = mvCursor_WaitToRepeat + mvCursor_RepeatTick;

    u32 keys = Controller::GetKeysDown();

    if( Controller::IsKeyPressed(Key::A) ) {
      _hook_reset();

      switch( submenu_index ) {
        // Open file
        case 0: {
          std::string name;

          if( file.IsOpen() && !saved ) {
            auto warn = MessageBox("Warning",
              "You are editing the file but it is not saved yet. Do you save ?", DialogType::DialogYesNo)();
            
            if( warn == true ) { // Yes
              save_file(file.GetName());
            }

            OSD::SwapBuffers();
          }

          

          break;
        }
      }

      _hook_init();
    }

    if( keys ) {
      if( tick == 0 || tick == mvCursor_WaitToRepeat || tick == mvCursor_RepeatReset ) {
        if( keys & DPadUp ) submenu_index--;
        if( keys & DPadDown ) submenu_index++;

        if( submenu_index < 0 )
          submenu_index = 0;
        else if( submenu_index >= entries.size() )
          submenu_index = entries.size() - 1;
      }

      if( tick == mvCursor_RepeatReset )
        tick = mvCursor_WaitToRepeat;
      else
        tick++;
    }
    else {
      tick = 0;
    }
  }

  int TextEditorImpl::submenu_open(Screen const& screen) {
    submenu_index = 0;
    
    while( 1 ) {
      Controller::Update();

      submenu_update();
      submenu_draw(screen);

      OSD::SwapBuffers();
      Sleep(Milliseconds(16));
    }

    return -1;
  }

}