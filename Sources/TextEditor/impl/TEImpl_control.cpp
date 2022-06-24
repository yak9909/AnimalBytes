#include <CTRPluginFramework.hpp>
#include "TEImpl.h"
#include "../Hotkeys.h"

namespace CTRPluginFramework {
  void TextEditorImpl::control(KeyboardEvent::EventType type, u32 key) {
    #define adjustX  if( cursor.x > data[cursor.y].length() ) cursor.x = data[cursor.y].length()



    if( key & Hotkeys::CursorUp ) {
      cursor.y = cursor.y ? cursor.y-- : 0;
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
        cursor.x = cursor.y < data.size() ? cursor.y++, 0 : data[cursor.y].length();
      }
    }


  }

}