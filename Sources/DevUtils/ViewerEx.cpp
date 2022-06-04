#include <string>
#include <vector>
#include <CTRPluginFramework.hpp>
#include "DevUtils/ViewerEx.h"
#include "Helpers.h"

namespace CTRPluginFramework::DevUtils {

  struct Item {
    enum class Kind {
      Int,
      UInt,
      Char,
      String,
      Custom,
      Struct
    };

    u32 addr;
    u32 bytesize;
    Kind kind;
    std::string val;
    std::vector<Item> list;

    Item() { }
    Item(u32 a, Kind k) :addr(a), kind(k) { }

    std::string get_type() const {

    }

    void read() const {
      switch( this->kind ) {
        case Kind::Int: {
          
        }
      }
    }
  };

  namespace {
    std::vector<Item> items;

    size_t draw_index;
  }

  void ViewerEx::gamefunc(MenuEntry* entry) {

  }

  void ViewerEx::menufunc(MenuEntry* entry) {

  }

  void ViewerEx::cmd_line(std::vector<std::string> const& args) {
  #define chk_argc(n) if( args.size() != n ) return
  #define chk_empty if( args.empty() ) return
  #define chk_s(n,k) if(get_strtype(args[n])!=k)return
    
    chk_empty;

    auto name = args[0];

    if( name == "add" ) {
      chk_args(3);

      chk_s(2, StringType::Integer);
      chk_s(3, StringType::Hex);


    }
    else if( name == "draw" ) {
      
    }

  }

    

}