#pragma once

#include <string>
#include <vector>
#include <memory>

namespace CTRPluginFramework {
  class TextEditorImpl;
  class TextEditor {
  public:
    TextEditor();
    TextEditor(std::string const& path);
    ~TextEditor();

    void open() const;
  
  private:
    std::unique_ptr<TextEditorImpl> impl;
  };
}