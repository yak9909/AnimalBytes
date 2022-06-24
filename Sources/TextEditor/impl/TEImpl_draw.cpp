#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  void TextEditorImpl::draw(Screen const& screen) {
    constexpr int char_width = 6;
    constexpr int linenum_width = 5;
    constexpr int height_max = 240 / 10;
    constexpr int width_max = 400 / char_width - linenum_width;

    static Clock clock;

    // line num
    screen.DrawRect(0, 0, linenum_width * char_width, 240, linenum_background);

    // background
    screen.DrawRect(linenum_width * char_width, 0, 400 - linenum_width * char_width, 240, Color(30, 30, 30));

    // lines
    {
      auto begin = scroll_pos.y;
      auto end = std::min<u32>(data.size(), begin + height_max);

      u32 dy = 0;

      for( ; begin < end; begin++, dy += 10 ) {
        auto const& line = data[begin];
        u32 dx = linenum_width * char_width;

        screen.Draw(Utils::Format("%5d", begin + 1), 0, dy, Color::White, linenum_background);

        if( line.length() > width_max ) {
          screen.Draw(line.substr(width_max), dx, dy, Color::White, background);
        }
        else {
          screen.Draw(line, dx, dy, Color::White, background);
        }
      }
    }

    // cursor
    if( scroll_pos.y <= cursor.y && cursor.y < scroll_pos.y + height_max && clock.HasTimePassed(Milliseconds(500)) ) {
      u32 cy = cursor.y - scroll_pos.y;
      screen.DrawRect(linenum_width * char_width + cursor.x * char_width, cy * 10, 1, 10, Color::Yellow);

      if( clock.HasTimePassed(Milliseconds(1000)) ) {
        clock.Restart();
      }
    }
  }

}