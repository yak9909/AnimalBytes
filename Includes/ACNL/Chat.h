#pragma once

#include <string>

namespace CTRPluginFramework::ACNL {
  class Chat {
    Chat() { }

  public:
    std::string text;

    static Chat clone_object();

    static bool is_open();

    static void read_text();
    static void write_text();

  };
}