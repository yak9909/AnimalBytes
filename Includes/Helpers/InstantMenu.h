#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <concepts>
#include <functional>
#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
  template <class T, std::string(*conv_fn)(T) = nullptr>
  class InstantMenuImpl {
    std::string title;
    std::vector<T> items;

    bool is_open;
    long index;
    long ret;

    static constexpr int edge = 16;
    static constexpr bool is_top = true;

    static inline int menu_draw_x;
    static inline int menu_draw_y;
    static inline int menu_width;
    static inline int menu_height;

    static constexpr int item_height = 14;
    static inline int item_draw_count;

    void draw(Screen const& screen) {
      auto const& background_color = Color::Black;

      // background
      screen.DrawRect(menu_draw_x, menu_draw_y, menu_width, menu_height, background_color);

      // draw title
      screen.Draw(this->title, menu_draw_x + 2, menu_draw_y + 1);
      screen.DrawRect(menu_draw_x + 2, menu_draw_y + item_height + 1, (this->title.length() + 2) * 9, 1, Color::White);

      // draw items
      {
        long begin = std::max<long>(0, index - (item_draw_count - 4));
        long end = std::min<long>(items.size(), begin + item_draw_count);
        long dy = menu_draw_y + item_height + 2;

        for( ; begin < end; begin++, dy += item_height ) {
          if constexpr( conv_fn == nullptr ) {
            if( index == begin ) {
              screen.Draw(items[begin], menu_draw_x + 2, dy, Color::White, Color::Blue);
            }
            else {
              screen.Draw(items[begin], menu_draw_x + 2, dy);
            }
          }
          else {
            if( index == begin ) {
              screen.Draw(conv_fn(items[begin]), menu_draw_x + 2, dy, Color::White, Color::Blue);
            }
            else {
              screen.Draw(conv_fn(items[begin]), menu_draw_x + 2, dy);
            }
          }
        }
      }
    }

    void control() {
      static int tick = -1;
      static constexpr int tickmax = 60;

      //u32 keys = hidKeysHeld();
      u32 keys = Controller::GetKeysDown();

      if( keys ) {
        tick++;

        if( tick == 0 || tick == tickmax ) {
          if( keys & Key::DPadUp ) index--;
          if( keys & Key::DPadDown ) index++;
          if( keys & Key::DPadLeft ) index -= 4;
          if( keys & Key::DPadRight ) index += 4;

          if( index < 0 ) index = items.size() - 1;
          else if( index >= items.size() ) index = 0;
        }

        if( tick >= tickmax ) tick = 0;
      }
      else {
        tick = -1;
      }

      if( Controller::IsKeyPressed(Key::A) ) {
        is_open = false;
        ret = index;
      }
      else if( Controller::IsKeyPressed(Key::B) ) {
        is_open = false;
        ret = -1;
      }
    }

  public:
    InstantMenuImpl(std::string const& title = "")
      : title(title),
        items({}),
        is_open(false),
        index(0)
    {
      set_menu_draw_pos(edge, edge);
    }

    InstantMenuImpl(std::string const& title, std::vector<T> const& items)
      : title(title),
        items(items),
        is_open(false),
        index(0)
    {
      set_menu_draw_pos(edge, edge);
    }

    void set_title(std::string const& title) {
      this->title = title;
    }

    void set_menu_draw_pos(int x, int y) {
      menu_draw_x = x;
      menu_draw_y = y;

      menu_width = (is_top ? 400 : 320) - menu_draw_x * 2;
      menu_height = 240 - menu_draw_y * 2;

      item_draw_count = menu_height / item_height;
    }

    void set_item(int index, T const& value) {
      items[index] = value;
    }

    void append_item(T const& val) {
      items.emplace_back(val);
    }

    void append_item(T&& val) {
      items.emplace_back(std::move(val));
    }

    std::vector<T> const& get_items() const {
      return this->items;
    }

    long open() {
      if( items.empty() ) {
        return -1;
      }

      is_open = true;

      Process::Pause();
      auto const& screen = OSD::GetTopScreen();

      while( is_open ) {
        Controller::Update();

        draw(screen);
        control();

        OSD::SwapBuffers();
        Sleep(Milliseconds(16));
      }

      Process::Play();

      return ret;
    }
  };

  using InstantMenu = InstantMenuImpl<std::string>;
  using InstantMenu_Int = InstantMenuImpl<int, std::to_string>;
}