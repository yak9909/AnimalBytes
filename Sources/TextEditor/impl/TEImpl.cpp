#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  TextEditorImpl::TextEditorImpl()
    : is_opening_submenu(false)
  {
  }

  TextEditorImpl::TextEditorImpl(std::string const& path)
    : is_opening_submenu(false)
  {
    //File::Open(file, path);
    
    data.open(path);

  }
}