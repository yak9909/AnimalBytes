#include <CTRPluginFramework.hpp>
#include <thread>
#include "Address.h"
#include "Chat.h"

namespace CTRPluginFramework::ACNL {

  bool Chat::is_open() {
    return *(u32*)(Addresses::Chat::BufferPointer) != 0;
  }

}