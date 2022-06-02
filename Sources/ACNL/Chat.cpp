#include <CTRPluginFramework.hpp>
#include <thread>
#include "ACNL/Address.h"
#include "ACNL/Chat.h"

namespace CTRPluginFramework::ACNL {

  Chat Chat::get_object() {
    Chat obj;

    u32 buffer_addr = *(u32*)Addresses::Chat::BufferPointer;
    u32 length = **(u32**)Addresses::Chat::TextLengthPointer;

    Process::ReadString(buffer_addr, obj.text, length, StringFormat::Utf16);
  }

  bool Chat::is_open() {
    return *(u32*)(Addresses::Chat::BufferPointer) != 0;
  }

}