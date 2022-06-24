#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  void TextEditorImpl::draw(Screen const& screen) {
    constexpr int char_width = 8;
    constexpr int linenum_width = 4;
    constexpr int line_len_max = 400 / char_width - linenum_width;

    // background
    screen.DrawRect(0, 0, 400, 240, Color(30, 30, 30));

    auto begin = scroll_pos.y;
    auto end = std::min<u32>(data.size() - 1, begin + 20);

    u32 dy = 0;
    std::string line;

    for( ; begin < end; begin++, dy += 10 ) {
      line = data[begin];

      if( line.length() > line_len_max ) {
        line = line.substr(0, line_len_max);
      }

      screen.Draw(line, linenum_width * 8, dy);
    }
  }

}