#include <CTRPluginFramework.hpp>
#include <thread>
#include "ACNL/Address.h"
#include "ACNL/Chat.h"

namespace CTRPluginFramework::ACNL {

  Chat Chat::clone_object() {
    Chat obj;

    // u32 buffer_addr = *(u32*)Addresses::Chat::BufferPointer;
    // u32 length = **(u32**)Addresses::Chat::TextLengthPointer;

    u32 buffer_addr;
    u32 length;

    if( !Process::Read32(Addresses::Chat::BufferPointer, buffer_addr) ) {
      return obj;
    }

    if( !Process::Read32(Addresses::Chat::TextLengthPointer, length) ) {
      return obj;
    }

    if( !Process::Read32(length + 0x8, length) ) {
      return obj;
    }

    Process::ReadString(buffer_addr, obj.text, length, StringFormat::Utf16);

    return obj;
  }

  bool Chat::is_open() {
    return *(u32*)(Addresses::Chat::BufferPointer) != 0;
  }

}