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

    bool add_callback();

    // 0   = No edited
    // 1   = 
    int open() const;
  
  private:
    std::unique_ptr<TextEditorImpl> impl;
  };
}