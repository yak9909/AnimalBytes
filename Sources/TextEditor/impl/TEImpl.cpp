#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  char const* TextEditorImpl::sys_submenu_entries[] = {
    "Open file",
    "Create a new file",
    "Save",
    "Save as ..."
  };

  TextEditorImpl::TextEditorImpl()
    : background(Color(30, 30, 30)),
      linenum_background(Color(50, 50, 50)),
      submenu_background(Color(50, 50, 50)),
      submenu_background_box(Color(100, 100, 100))
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