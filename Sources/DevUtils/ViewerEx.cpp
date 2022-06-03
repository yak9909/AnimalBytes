#include <string>
#include <vector>
#include <CTRPluginFramework.hpp>
#include "DevUtils/ViewerEx.h"

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

    

}