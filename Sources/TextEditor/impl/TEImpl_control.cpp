#include <CTRPluginFramework.hpp>
#include "TEImpl.h"
#include "../Hotkeys.h"

constexpr int keyRepeatWait = 300;

namespace CTRPluginFramework {
  void TextEditorImpl::control(KeyboardEvent::EventType type, u32 key) {
    #define adjustX  if( cursor.x > data[cursor.y].length() ) cursor.x = data[cursor.y].length()

    static Clock clock;

    if( key && (type == KeyboardEvent::KeyPressed || clock.HasTimePassed(Milliseconds(keyRepeatWait))) ) {
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

      if( type == KeyboardEvent::KeyPressed ) {
        clock.Restart();
      }
      else if( clock.HasTimePassed(Milliseconds(keyRepeatWait + 100)) ) {
        clock = Milliseconds(keyRepeatWait);
      }

      forceDrawCursor = true;
    }
    else if( type == KeyboardEvent::KeyReleased ) {
      forceDrawCursor = false;
    }


  }

}