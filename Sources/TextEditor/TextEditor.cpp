#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"

namespace CTRPluginFramework {
  TextEditor::TextEditor()
  {
  }

  TextEditor::TextEditor(std::string const& path)
    : impl(new TextEditorImpl(path))
  {
  }

  TextEditor::~TextEditor()
  {
  }

  int TextEditor::open() const {
    impl->open();
  }

}