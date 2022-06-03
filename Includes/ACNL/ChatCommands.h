#pragma once

#include <map>
#include <string>
#include <vector>

namespace CTRPluginFramework::ACNL {
  class ChatCommands {
    using Arguments = std::vector<std::string>;
    using CommandFuncPointer = void(*)(Arguments const&);

    bool is_running;
    std::map<std::string, CommandFuncPointer> func_map;

  public:

    static ChatCommands* get_instance();

    static void init();

    static bool append_func(std::string const& name, CommandFuncPointer fp);

    static void catch_command_execute();

    static void call_back();

    static void dispose();
  };
}