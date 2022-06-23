#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"

namespace CTRPluginFramework {
  TextEditorImpl::TextEditorImpl() {
  }

  TextEditorImpl::TextEditorImpl(std::string const& path) {
    //File::Open(file, path);

    data.open(path);

  }
}