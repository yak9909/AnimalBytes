#pragma once

#include <CTRPluginFramework.hpp>
#include "../CTextData/CTextData.h"

namespace CTRPluginFramework {
  class TextEditorImpl {
    friend class TextEditor;

    //File file;
    CTextData data;


    TextEditorImpl();
    TextEditorImpl(std::string const& path);

    void draw(Screen const& screen);

    // 0  = No edited
    // 1  = Aborted (edited)
    // 2  = Saved
    int open();

  public:
    ~TextEditorImpl() = default;
  };
}