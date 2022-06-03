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

      for( auto&& c : str ) {
        if( !isdigit(c) ) goto other;
      }

      return StringType::Integer;
    }
    else if( isalpha(ch) ) {
      return StringType::Char;
    }
    else if( isspace(ch) ) {
      return StringType::Space;
    }

  other:;
    return StringType::Other;
  }
}