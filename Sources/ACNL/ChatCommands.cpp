#include <CTRPluginFramework.hpp>
#include <thread>
#include "ACNL/Address.h"
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "Helpers/Strings.hpp"

namespace CTRPluginFramework::ACNL {

  static constexpr auto cmd_run_hotkey = Key::B | Key::R;

  static ChatCommands* instance;

  ChatCommands::ChatCommands() {

  }

  ChatCommands::~ChatCommands() {
    is_running = false;

    thread->Join(1);
    delete thread;
  }

  ChatCommands* ChatCommands::get_instance() {
    if( !instance ) {
      instance = new ChatCommands();
    }

    return instance;
  }

  bool ChatCommands::append_func(std::string const& name, CommandFuncPointer fp) {
    if( instance->func_map.contains(name) ) {
      return false;
    }

    instance->func_map[name] = fp;
    return true;
  }

  void ChatCommands::catch_command_execute() {
    u32 keys = Controller::GetKeysDown();

    if( keys & cmd_run_hotkey ) {
      Chat chat = Chat::clone_object();

      std::string name;
      auto args = trim_string(chat.text, ' ');

      name = args[0];
      args.erase(args.begin());

      auto fp = instance->func_map[name];

      if( fp == nullptr ) {

      }
      else {
        fp(args);
      }
    }
  }

  void ChatCommands::main_routine(void*) {

    while( instance->is_running ) {
      if( !Chat::is_open() ) {
        continue;
      }

      catch_command_execute();
    }

  }

  void ChatCommands::run() {
    get_instance();

    s32 prio;
    svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);

    instance->thread = new ThreadEx(ChatCommands::main_routine, 0x1000, prio, 0);

  }

  void ChatCommands::dispose() {
    delete instance;
  }

}