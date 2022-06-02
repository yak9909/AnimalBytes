#pragma once

#include <string>

namespace CTRPluginFramework::ACNL {
  class Chat {
    Chat() { }

  public:
    std::string text;

    static Chat get_object();

    static bool is_open();

  };
}