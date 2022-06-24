#pragma once

#include <CTRPluginFramework.hpp>
#include "CTextData.h"

namespace CTRPluginFramework {
  class TextEditor;
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
    UpdateFlags update_flags;
    bool is_opening_submenu;

    TextEditorImpl();
    TextEditorImpl(std::string const& path);

    bool add_callback();

    void draw(Screen const& screen);
    void draw_submenu(Screen const& screen);

    int open_menu();

    // 0  = Saved
    // 1  = No Edited
    // 2  = Aborted (edited)
    int open();

    void update();
    void control();

    static void _hook_init();
    static void _hook_reset();
    static void _KbdImpl_RenderTop_hook(void*);

  public:
    ~TextEditorImpl() = default;
  };
}