#include <CTRPluginFramework.hpp>
#include <vector>

#define  OSDMSG_MAX_COUNT  8

extern "C" {
  extern u32 _hookFn_OSDMessage_ctor;

  // OSDImpl::OSDMessage::OSDMessage
  extern u32 _ZN18CTRPluginFramework7OSDImpl10OSDMessageC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ColorESC_;
};

namespace CTRPluginFramework {
  static constexpr u32 asmjump = 0xE51FF004; // ldr pc, [pc, #-4]

  class ProcessImpl {
  public:
    static Mutex   MemoryMutex;
    static std::vector<MemInfo> MemRegions;
  };

  class OSDImpl {
  public:
    struct OSDMessage {
      // OSDMessage(const std::string &str, const Color &fg, const Color &bg);
    };
    
    static std::vector<OSDMessage*> Notifications;
  };

  extern "C" void _hookFnHelper_OSDMessageElementDeleter_() {
    if( OSDImpl::Notifications.size() > OSDMSG_MAX_COUNT ) {
      OSDImpl::Notifications.erase(OSDImpl::Notifications.begin());
    }
  }

  static bool c_Process_CheckAddress(u32 addr) {
    Lock lock(ProcessImpl::MemoryMutex);

    if( addr >= 0x838000 && addr < 0x839000 )
      return false;

    for( auto const& memInfo : ProcessImpl::MemRegions ) {
      if( memInfo.base_addr <= addr && addr < memInfo.base_addr + memInfo.size ) {
        return true;
      }
    }

    return false;
  }
  
  // ------------------- //
  //  Initalize hooks    //
  // ------------------- //
  void InitHooks() {
    u32* ptr;

    // Process::CheckAddress
    //   return false if address is reserved by AnimalBytes
    ptr = (u32*)&Process::CheckAddress;
    ptr[0] = asmjump;
    ptr[1] = (u32)&c_Process_CheckAddress;

    // OSDImpl::OSDMessage::OSDMessage(...)
    //   erase first element in OSDImpl::Notifications when size overed OSDMSG_MAX_COUNT
    ptr = &_ZN18CTRPluginFramework7OSDImpl10OSDMessageC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ColorESC_;
    ptr[0] = asmjump;
    ptr[1] = (u32)&_hookFn_OSDMessage_ctor;


  }
}