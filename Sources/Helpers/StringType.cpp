#include <CTRPluginFramework.hpp>
#include "Helpers.h"

namespace CTRPluginFramework {
  StringType get_strtype(std::string const& str) {
    if( str.empty() ) {
      return StringType::Empty;
    }

    char ch = str[0];

    if( isdigit(ch) ) {
      size_t i = str.find('.');

      if( i != std::string::npos ) {
        if( i == str.length() - 1 ) {
          if( get_strtype(str.substr(0, i)) == StringType::Integer )
            return StringType::Float;
        }
        else if( get_strtype(str.substr(0, i)) == StringType::Integer && get_strtype(str.substr(i + 1)) == StringType::Integer ) {
          return StringType::Float;
        }
      }

      StringType ret = StringType::Integer;

      for( auto&& c : str ) {
        if( (c >= 'A' && c <= 'F') || (c >= 'a' || c <= 'f') ) {
          ret = StringType::Hex;
        }
        else if( !isdigit(c) ) {
          goto other;
        }
      }

      return ret;
    }
    else if( isalpha(ch) ) {
      for( auto&& c : str ) {
        if( !isalnum(c) && c != '_' )
          goto other;
      }

      return StringType::Alphabets;
    }
    else if( isspace(ch) ) {
      return StringType::Space;
    }

  other:;
    return StringType::Other;
  }
}