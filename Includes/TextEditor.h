#pragma once

#include <string>
#include <vector>
#include <memory>

namespace CTRPluginFramework {
  class TextEditorImpl;
  class TextEditor {
  public:
    // not used ??
    enum class UpdateFlags : uint32_t {
      None = 0,

      // Redraw lines within screen
      Text = BIT(1),

      All = 0xFFFFFFFF
    };

    enum class Result {
      Saved,
      Aborted,
      NoEdited
    };

    struct EventType {
      enum Kind {
        CharInserted,
        CharDeleted,

        KeyDown,
        KeyPressed,
        KeyReleased
      };

      Kind kind;
      Key keycode{ };
    };

    using EventFuncPointer = UpdateFlags(*)(TextEditor&, EventType&);
    

    TextEditor();
    TextEditor(std::string const& path);
    ~TextEditor();

    // 
    void add_event(EventFuncPointer func);

    // 
    void add_submenu_entry(std::string const& name, EventFuncPointer func);

    TextEditor::Result open() const;
  
    std::vector<std::string>& get_source();

    static TextEditor* get_instance();

  private:
    friend class TextEditorImpl;
    std::unique_ptr<TextEditorImpl> impl;
  };
}