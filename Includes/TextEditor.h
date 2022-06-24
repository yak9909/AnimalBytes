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

    // in 
    bool add_callback();

    // 0   = No edited
    // 1   = 
    int open() const;
  
    static TextEditor* get_instance();

  private:
    friend class TextEditorImpl;
    std::unique_ptr<TextEditorImpl> impl;
  };
}