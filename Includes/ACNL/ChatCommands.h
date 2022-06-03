#pragma once

#include <map>
#include <string>
#include <vector>

namespace CTRPluginFramework::ACNL {
  class ChatCommands {
    using Arguments = std::vector<std::string>;
    using CommandFuncPointer = void(*)(Arguments const&);
    using HookFuncPointer = bool(*)(std::string const&);

    bool is_running;
    HookFuncPointer hook;
    std::map<std::string, CommandFuncPointer> func_map;

    ChatCommands();

  public:

    static ChatCommands* get_instance();

    // initialize
    static void init();

    // append function with name key
    static bool append_func(std::string const& name, CommandFuncPointer fp);

    // set hook function after pressed hotkey
    static void set_hook(HookFuncPointer func);

    static void catch_command_execute();

    static void call_back();

    static void dispose();
  };
}