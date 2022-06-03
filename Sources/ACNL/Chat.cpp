#include <CTRPluginFramework.hpp>
#include <thread>
#include "ACNL/Address.h"
#include "ACNL/Chat.h"

namespace CTRPluginFramework::ACNL {
  
	static int lenByte(unsigned char c) {
		if ((c >= 0x00) && (c <= 0x7f)) return 1;
		else if ((c >= 0xc2) && (c <= 0xdf)) return 2;
		else if ((c >= 0xe0) && (c <= 0xef)) return 3;
		else if ((c >= 0xe0) && (c <= 0xef)) return 4;

		return 0;
	}

  static int lenUtf8(std::string const& str) {
		auto _pstr = str.c_str();

		int i = 0;
		int len = 0;

		while( _pstr[i] != '\0' ) {
			len++;
			i += lenByte(_pstr[i]);
		}

		return len;
	}

  Chat Chat::clone_object() {
    Chat obj{ };

    u32 buffer_addr;
    u32 length = get_length();

    if( !Process::Read32(Addresses::Chat::BufferPointer, buffer_addr) ) {
      return obj;
    }

    Process::ReadString(buffer_addr, obj.text, 32 * 2, StringFormat::Utf16);

    return obj;
  }

  bool Chat::is_open() {
    return *(u32*)(Addresses::Chat::BufferPointer) != 0;
  }

  u8 Chat::get_length() {
    u32 lengthptr;
    u8 length;

    if( !Process::Read32(Addresses::Chat::TextLengthPointer, lengthptr) ) {
      return 0;
    }

    if( !Process::Read8(lengthptr + 0x8, length) ) {
      return 0;
    }

    return length;
  }

  std::string Chat::read_text() {
    u32 buffer_addr;
    u32 length = get_length();
    std::string ret;

    if( !Process::Read32(Addresses::Chat::BufferPointer, buffer_addr) ) {
      return ret;
    }

    Process::ReadString(buffer_addr, ret, 32 * 2, StringFormat::Utf16);
    return ret;
  }

  void Chat::write_text(std::string const& text) {
    u32 buffer_addr;
    u32 lengthptr;
    u32 len = lenUtf8(text);
    
    if( !Process::Read32(Addresses::Chat::BufferPointer, buffer_addr) ) {
      return;
    }

    if( !Process::Read32(Addresses::Chat::TextLengthPointer, lengthptr) ) {
      return;
    }

    Process::Write32(lengthptr + 8, len);
    Process::WriteString(buffer_addr, text, StringFormat::Utf16);
  }

}