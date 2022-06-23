#pragma once

#include <CTRPluginFramework.hpp>
#include "CTextData.h"

namespace CTRPluginFramework {
  class TextEditorImpl {
    friend class TextEditor;

    enum class UpdateFlags : uint32_t {
      None = 0,

      // Redraw lines within screen
      Text = BIT(1),
      

      All = 0xFFFFFFFF
    };

    struct Callback {
      using FuncPointer = UpdateFlags(*)(TextEditor*);
    };
    
    //File file;
    CTextData data;



    TextEditorImpl();
    TextEditorImpl(std::string const& path);

    bool add_callback();

    void draw(Screen const& screen);
    void draw_menu(Screen const& screen);

    int open_menu();

    // 0  = Saved
    // 1  = No Edited
    // 2  = Aborted (edited)
    int open();

    void update();


  public:
    ~TextEditorImpl() = default;
  };
}