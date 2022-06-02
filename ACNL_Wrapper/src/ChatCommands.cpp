#include <CTRPluginFramework.hpp>
#include <thread>
#include "Address.h"
#include "Chat.h"
#include "ChatCommands.h"

namespace CTRPluginFramework::ACNL {

  static ChatCommands* instance;

  ChatCommands::ChatCommands() {

  }

  ChatCommands::~ChatCommands() {
    is_running = false;

    thread->join();
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
    
  }

  void ChatCommands::main_routine() {

    while( instance->is_running ) {
      if( !Chat::is_open() ) {
        continue;
      }

      catch_command_execute();
    }

  }

  void ChatCommands::run() {
    get_instance();

    instance->thread = new std::thread(ChatCommands::main_routine);

  }

  void ChatCommands::dispose() {
    delete instance;
  }

}