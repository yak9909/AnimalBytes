#pragma once

#include <string>

namespace CTRPluginFramework::ACNL {
  class Chat {
    Chat() :text("") { }

  public:
    std::string text;

    static Chat clone_object();

    static bool is_open();
    static u8 get_length();

    static std::string read_text();
    static void write_text(std::string const& text);

  };
}