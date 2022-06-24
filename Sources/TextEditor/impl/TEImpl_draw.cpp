#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  void TextEditorImpl::draw(Screen const& screen) {
    // background
    screen.DrawRect(0, 0, 400, 240, Color(30, 30, 30));


  }

}