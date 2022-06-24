#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
  class TextEditorImpl {
    friend class TextEditor;

    File file;

    TextEditorImpl();
    TextEditorImpl(std::string const& path);

    void draw(Screen const& screen);
    void open();

  public:
    ~TextEditorImpl() = default;
  };
}