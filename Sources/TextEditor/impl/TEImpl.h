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

    bool append_

    void draw(Screen const& screen);
    void draw_menu(Screen const& screen);

    int open_menu();

    // 0  = No edited
    // 1  = Aborted (edited)
    // 2  = Saved
    int open();

    void update();


  public:
    ~TextEditorImpl() = default;
  };
}