#include <CTRPluginFramework.hpp>
#include "TEImpl.h"
#include "../Hotkeys.h"

constexpr int keyRepeatWait = 300;
constexpr int waitRepeatMilli = 30;

namespace CTRPluginFramework {
  void TextEditorImpl::control(KeyboardEvent::EventType type, u32 key) {
    #define adjustX  if( cursor.x > data[cursor.y].length() ) cursor.x = data[cursor.y].length()

    static Clock clock;
    static Clock clock2;
    static bool flag;

    if( key == 0 ) {
      return;
    }

    switch( type ) {
      case KeyboardEvent::EventType::KeyPressed: {

        if( key & Hotkeys::Selecting ) {
          is_selecting = true;
          select_started_pos = cursor;
        }

        break;
      }

      case KeyboardEvent::EventType::KeyDown: {

        if( key & Hotkeys::Selecting ) {
          is_selecting = false;
        }

        break;
      }

      case KeyboardEvent::EventType::KeyReleased: {
        forceDrawCursor = false;
        break;
      }
    }

    if( type == KeyboardEvent::EventType::KeyPressed || (clock.HasTimePassed(Milliseconds(keyRepeatWait)) && clock2.HasTimePassed(Milliseconds(waitRepeatMilli))) ) {
      auto cursor_bak = cursor;
      
      if( key & Hotkeys::CursorUp ) {
        if( --cursor.y < 0 ) cursor.y = 0;
        adjustX;
      }

      if( key & Hotkeys::CursorDown ) {
        if( ++cursor.y >= data.size() ) {
          cursor.y--;
        }
        else {
          adjustX;
        }
      }

      if( key & Hotkeys::CursorLeft ) {
        if( --cursor.x < 0 ) {
          cursor.x = cursor.y > 0 ? data[--cursor.y].length() : 0;
        }
      }

      if( key & Hotkeys::CursorRight ) {
        if( ++cursor.x > data[cursor.y].length() ) {
          cursor.x = cursor.y < (signed)data.size() - 1 ? cursor.y++, 0 : data[cursor.y].length();
        }
      }

      if( key & Hotkeys::Enter ) {
        newline();
      }

      if( key & Hotkeys::Backspace ) {
        delete_char();
      }

      if( cursor.y != cursor_bak.y ) {
        if( cursor.y < scroll_pos.y ) {
          scroll_pos.y = cursor.y;
        }
        else if( cursor.y >= scroll_pos.y + 24 ) {
          scroll_pos.y = cursor.y - 23;
        }
      }

      if( key & Hotkeys::ScreenUp ) {
        if( --scroll_pos.y < 0 )
          scroll_pos.y = 0;
      }

      if( key & Hotkeys::ScreenDown ) {
        auto maxval = std::max<int>((int)data.size() - 10, 0);

        if( ++scroll_pos.y > maxval ) {
          scroll_pos.y = maxval;
        }
      }

      if( key & Hotkeys::ScreenLeft ) {
        // todo
      }

      if( key & Hotkeys::ScreenRight ) {
        // todo
      }

      if( type == KeyboardEvent::KeyPressed ) {
        clock.Restart();
      }

      clock2.Restart();

      forceDrawCursor = true;
    }


  }

}