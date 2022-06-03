#include <cstdio>
#include <string>
#include <vector>
#include <types.h>

namespace CTRPluginFramework
{
  std::string   Hex(u8 x)
  {
    char  buffer[3];

    sprintf(buffer, "%02X", x);
    return (std::string(buffer));
  }

  std::string   Hex(u16 x)
  {
    char  buffer[5];

    sprintf(buffer, "%04X", x);
    return (std::string(buffer));
  }

  std::string   Hex(u32 x)
  {
    char  buffer[9];

    sprintf(buffer, "%08X", x);
    return (std::string(buffer));
  }

  std::string   Hex(u64 x)
  {
    char  buffer[17];

    sprintf(buffer, "%016llX", x);
    return (std::string(buffer));
  }

  std::string   Hex(float x)
  {
    char  buffer[9];

    sprintf(buffer, "%08X", (u32)x);
    return (std::string(buffer));
  }

  std::string   Hex(double x)
  {
    char  buffer[17];

    sprintf(buffer, "%016llX", (u64)x);
    return (std::string(buffer));
  }
  
  std::vector<std::string> trim_string(std::string const& str, char c) {
    std::vector<std::string> vec;
    std::string s;

    for( char ch : str ) {
      if( ch == c ) {
        vec.emplace_back(s);
        s.clear();
      }
      else {
        s += ch;
      }
    }

    if( !s.empty() ) {
      vec.emplace_back(s);
    }

    return vec;
  }
}
