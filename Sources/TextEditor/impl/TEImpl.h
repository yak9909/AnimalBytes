#pragma once

#include <CTRPluginFramework.hpp>
#include "TextEditor.h"

namespace CTRPluginFramework {
  class TextEditor;
  class TextEditorImpl {
    friend class TextEditor;

    struct Point {
      int x, y;
    };

    struct SubmenuEntry {
      std::string const name;
      TextEditor::EventFuncPointer const func;
      
      explicit SubmenuEntry(std::string const& name, TextEditor::EventFuncPointer func);
    };

    Color const background;
    Color const linenum_background;

    Color const submenu_background;
    Color const submenu_background_box;

    File file;
    bool saved = 0;

    Point cursor{ };
    Point scroll_pos{ };
    Clock cursor_clock;
    bool forceDrawCursor = 0;

    bool is_selecting = 0;
    Point select_started_pos{ };

    std::vector<std::string> data{ "" };

    TextEditor::EventType event;
    std::vector<TextEditor::EventFuncPointer> event_funcs;
    std::vector<SubmenuEntry> submenu_user_entries;

    //UpdateFlags update_flags;
    bool is_opening_submenu = 0;
    int submenu_index = 0;

    TextEditorImpl();
    TextEditorImpl(std::string const& path);

    void insert_char(char ch);
    void delete_char();
    void newline();

    void draw(Screen const& screen);
    void draw_bottom(Screen const& screen);

    void control(KeyboardEvent::EventType type, u32 key);
    TextEditor::Result open();

    void submenu_draw(Screen const& screen);
    void submenu_update();
    int submenu_open(Screen const& screen);

    static void _hook_init();
    static void _hook_reset();
    static void _KbdImpl_RenderTop_hook(void*);
    static void _KbdImpl_RenderBottom_hook(void*);
    static void keyboardEvent(Keyboard& kbd, KeyboardEvent& ev);

    static char const* sys_submenu_entries[];

  public:
    ~TextEditorImpl() = default;
  };
}