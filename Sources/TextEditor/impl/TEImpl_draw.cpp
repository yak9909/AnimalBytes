#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  void TextEditorImpl::draw(Screen const& screen) {
    constexpr int char_width = 6;
    constexpr int linenum_len = 5;
    constexpr int linenum_width = linenum_len * char_width + 2;
    constexpr int height_max = 240 / 10;
    constexpr int width_max = (400 - linenum_width - 4) / char_width;
    constexpr char fmt[] = { '%', '0' + linenum_len, 'd', 0 };

    // line num
    screen.DrawRect(0, 0, linenum_width, 240, linenum_background);

    // sepalator
    screen.DrawRect(linenum_width, 0, 1, 240, Color::White);

    // background
    screen.DrawRect(linenum_width + 1, 0, 400 - linenum_width - 1, 240, Color(30, 30, 30));

    // lines
    {
      auto begin = scroll_pos.y;
      auto end = std::min<u32>(data.size(), begin + height_max);

      u32 dy = 0;

      for( ; begin < end; begin++, dy += 10 ) {
        auto const& line = data[begin];
        u32 dx = linenum_width + 3;

        screen.Draw(Utils::Format(fmt, begin + 1), 0, dy, Color::White, linenum_background);

        if( line.length() > width_max ) {
          screen.Draw(line.substr(width_max), dx, dy, Color::White, background);
        }
        else {
          screen.Draw(line, dx, dy, Color::White, background);
        }
      }
    }

    // cursor
    if( scroll_pos.y <= cursor.y && cursor.y < scroll_pos.y + height_max && (forceDrawCursor || cursor_clock.HasTimePassed(Milliseconds(600))) ) {
      u32 cy = cursor.y - scroll_pos.y;
      screen.DrawRect(linenum_width + cursor.x * char_width + 3, cy * 10, 1, 10, Color::Yellow);

      if( !forceDrawCursor && cursor_clock.HasTimePassed(Milliseconds(1200)) ) {
        cursor_clock.Restart();
      }
    }

    // debug
    if( _draw_addr ) {
      screen.Draw(Utils::Format("%08X", _dbg_addr_value), 0, 0);
    }
  }

  void TextEditorImpl::draw_bottom(Screen const& screen) {

    u32 dy = 0;

    if( is_selecting ) {
      screen.Draw("selecting...", 0, dy, Color::Black, Color::ForestGreen);
      dy += 10;
    }

  }

}