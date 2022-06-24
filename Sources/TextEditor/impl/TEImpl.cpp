#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  TextEditorImpl::TextEditorImpl()
    : background(Color(30, 30, 30)),
      is_opening_submenu(false)
  {
  }

  TextEditorImpl::TextEditorImpl(std::string const& path)
    : TextEditorImpl()
  {
    File::Open(file, path);
    
    LineReader reader{ file };

    for( std::string line; reader(line); ) {
      data.emplace_back(line);
    }

  }
}