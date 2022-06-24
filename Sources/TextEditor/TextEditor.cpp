#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TextEditorImpl.h"

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

  void TextEditor::open() const {
    impl->open();
  }

}