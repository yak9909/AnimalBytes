#pragma once

#include <map>
#include <string>

namespace CTRPluginFramework::ACNL {
  class ChatCommands {
    using Arguments = std::vector<std::string>;
    using CommandFuncPointer = void(*)(std::string const&, Arguments const&);

    bool is_running;
    std::thread* thread;
    std::map<std::string, CommandFuncPointer> func_map;

    ChatCommands();
    ~ChatCommands();

  public:

    static ChatCommands* get_instance();

    static bool append_func(std::string const& name, CommandFuncPointer fp);

    static void catch_command_execute();

    static void main_routine();

    static void run();

    static void dispose();
  };
}