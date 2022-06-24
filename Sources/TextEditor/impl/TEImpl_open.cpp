#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"
#include "../Hotkeys.h"

extern "C" void _ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv(void*);

namespace CTRPluginFramework {
  static u32 _hook_bak[2];

  void TextEditorImpl::_KbdImpl_RenderTop_hook(void*) {
    auto& te = *TextEditor::get_instance()->impl;
    auto const& screen = OSD::GetTopScreen();
    
    te.draw(screen);

  }

  void TextEditorImpl::_hook_init() {
    u32* ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv;

    memcpy(_hook_bak, ptr, sizeof(_hook_bak));

    ptr[0] = 0xE51FF004;  // ldr pc, [pc, #-4]
    ptr[1] = (u32)TextEditorImpl::_KbdImpl_RenderTop_hook;
  }

  void TextEditorImpl::_hook_reset() {
    u32* ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv;
    memcpy(ptr, _hook_bak, sizeof(_hook_bak));
    
  }

  int TextEditorImpl::open() {
    Keyboard kbd;

    kbd.DisplayTopScreen = true;

    kbd.OnKeyboardEvent([] (Keyboard& kbd, KeyboardEvent& event) -> void {

      auto& editor = *TextEditor::get_instance()->impl;

      switch( event.type ) {
        case KeyboardEvent::CharacterAdded:
          editor.insert_char();

        case KeyboardEvent::KeyPressed:
        case KeyboardEvent::KeyDown:
        case KeyboardEvent::KeyReleased:
          editor.control(event.type, event.affectedKey);
          break;
      }

      kbd.GetInput().clear();

    });

    _hook_init();

    std::string s;
    kbd.Open(s);

    _hook_reset();

    return 0;
  }

  void TextEditorImpl::update() {

  }

}