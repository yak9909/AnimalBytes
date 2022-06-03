#include <CTRPluginFramework.hpp>
#include <thread>
#include "ACNL/Address.h"
#include "ACNL/Chat.h"
#include "ACNL/ChatCommands.h"
#include "Helpers/Strings.h"

namespace CTRPluginFramework::ACNL {

  static constexpr auto cmd_run_hotkey = Key::B | Key::R;

  static ChatCommands* instance = nullptr;

  ChatCommands::ChatCommands()
    : is_running(false)
  {
  }

  ChatCommands* ChatCommands::get_instance() {
    if( !instance ) {
      instance = new ChatCommands();
    }

    return instance;
  }

  void ChatCommands::init() {
    ChatCommands::get_instance();
  }

  bool ChatCommands::append_func(std::string const& name, CommandFuncPointer fp) {
    if( ChatCommands::get_instance()->func_map.contains(name) ) {
      return false;
    }

    ChatCommands::get_instance()->func_map[name] = fp;
    return true;
  }

  void ChatCommands::append_hook(HookFuncPointer func) {
    ChatCommands::get_instance()->hooks.emplace_back(func);
  }

  void ChatCommands::catch_command_execute() {
    auto inst = ChatCommands::get_instance();

    if( Controller::IsKeysPressed(cmd_run_hotkey) ) {
      Chat chat = Chat::clone_object();

      if( chat.text.empty() )
        return;

      for( auto&& h : inst->hooks ) {
        if( h(chat.text) ) {
          return;
        }
      }

      std::string name;
      auto args = trim_string(chat.text, ' ');

      name = args[0];
      args.erase(args.begin());

      auto fp = inst->func_map[name];

      if( fp == nullptr ) {
        Chat::write_text(Utils::Format("\"%s\" is not defined.", name.c_str()));
      }
      else {
        fp(args);
      }
    }
  }

  void ChatCommands::call_back() {

    if( !Chat::is_open() ) {
      return;
    }

    catch_command_execute();

  }


}