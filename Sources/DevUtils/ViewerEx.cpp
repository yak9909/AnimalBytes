#include <string>
#include <vector>
#include <CTRPluginFramework.hpp>
#include "DevUtils/ViewerEx.h"
#include "Helpers/StringType.h"

namespace CTRPluginFramework::DevUtils {

  struct Item {
    enum class Kind {
      Int,
      UInt,
      Char,
      String
    };

    u32 addr;
    Kind kind;

    Item() { }
    Item(u32 a, Kind k) :addr(a), kind(k) { }

    std::string read() const {
      std::string ret;

      switch( this->kind ) {

      }

      return ret;
    }
  };


  void ViewerEx::gamefunc(MenuEntry* entry) {

  }

  void ViewerEx::menufunc(MenuEntry* entry) {

  }

  void ViewerEx::cmd_line(std::vector<std::string> const& args) {
  #define chk_argc(n) if( args.size() != n ) return
  #define chk_empty if( args.empty() ) return
    
    chk_empty;

    auto name = args[0];

    if( name == "add" ) {
      chk_args(3);


    }
  }

    

}