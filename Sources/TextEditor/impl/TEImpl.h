#pragma once

#include <CTRPluginFramework.hpp>
#include "TextEditor.h"

namespace CTRPluginFramework {
  class TextEditor;
  class TextEditorImpl {
    friend class TextEditor;

    struct Point {
      u32 x, y;
    };

    Color const background;
    Color const linenum_background;

    File file;

    Point cursor{ 0 };
    Point scroll_pos{ 0 };
    std::vector<std::string> data{ "" };

    TextEditor::EventType event;
    std::vector<TextEditor::EventFuncPointer> event_funcs;

    //UpdateFlags update_flags;
    bool is_opening_submenu;

    TextEditorImpl();
    TextEditorImpl(std::string const& path);

    void draw(Screen const& screen);
    void draw_submenu(Screen const& screen);

    int open_menu();

    // 0  = Saved
    // 1  = No Edited
    // 2  = Aborted (edited)
    int open();

    void insert_char(char ch);
    void delete_char();

    void update();
    void control(KeyboardEvent::EventType type, u32 key);

    static void _hook_init();
    static void _hook_reset();
    static void _KbdImpl_RenderTop_hook(void*);

  public:
    ~TextEditorImpl() = default;
  };
}