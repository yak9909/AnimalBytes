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
    
    saved = 0;
  }

  void TextEditorImpl::delete_char() {
    if( cursor.x == 0 ) {
      if( cursor.y == 0 ) {
        return;
      }

      if( data[cursor.y].empty() ) {
        cursor.x = data[cursor.y - 1].length();
        data.erase(data.begin() + cursor.y);
        cursor.y--;
        return;
      }

      cursor.x = data[cursor.y - 1].length();
      data[cursor.y - 1] += data[cursor.y];
      data.erase(data.begin() + cursor.y);

      cursor.y--;
      return;
    }

    auto& line = data[cursor.y];

    line.erase(line.begin() + --cursor.x);

    saved = 0;
  }

  void TextEditorImpl::newline() {
    auto& line = data[cursor.y];

    if( cursor.x == line.length() ) {
      cursor.x = 0;
      
      if( ++cursor.y >= data.size() ) {
        data.emplace_back();
      }
      else {
        data.insert(data.begin() + cursor.y, "");
      }

      return;
    }

    cursor.y++;

    if( cursor.y >= data.size() ) {
      data.emplace_back(line.substr(cursor.x));
    }
    else {
      data.insert(data.begin() + cursor.y, line.substr(cursor.x));
    }

    data[cursor.y - 1] = data[cursor.y - 1].substr(0, cursor.x);
    cursor.x = 0;

    saved = 0;
  }

}