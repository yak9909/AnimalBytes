#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  void TextEditorImpl::insert_char(char ch) {
    auto& line = data[cursor.y];

    if( cursor.x == line.length() ) {
      line += ch;
    }
    else {
      line.insert(line.begin() + cursor.x, ch);
    }

    cursor.x++;
  }

  void TextEditorImpl::delete_char() {
    if( cursor.x == 0 ) {
      if( cursor.y == 0 ) {
        return;
      }

      cursor.x = data[cursor.y - 1].length();
      data[cursor.y - 1] += data[cursor.y];

      cursor.y--;
      return;
    }

    auto& line = data[cursor.y];

    line.erase(line.begin() + --cursor.x);
  }

}