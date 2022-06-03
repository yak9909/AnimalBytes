#pragma once

#include <map>
#include <string>

namespace CTRPluginFramework::ACNL {
  class ChatCommands {
    using Arguments = std::vector<std::string>;
    using CommandFuncPointer = void(*)(Arguments const&);

    bool is_running;
    ThreadEx* thread;
    std::map<std::string, CommandFuncPointer> func_map;

    ChatCommands()
      : is_running(false),
        thread(nullptr),
        func_map({ })
    {
    }

    ~ChatCommands() {
      is_running = false;

      thread->Join(1);
      delete thread;
    }

  public:

    static ChatCommands* get_instance();

    static void init();

    static bool append_func(std::string const& name, CommandFuncPointer fp);

    static void catch_command_execute();

    static void main_routine(void *);

    static void run();

    static void dispose();
  };
}