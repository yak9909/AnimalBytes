#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"
#include "../Hotkeys.h"

extern "C" {
  void _ZN18CTRPluginFramework12KeyboardImpl3RunEv(void*);
  void _ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv(void*);
  void _ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv(void*);
};

namespace CTRPluginFramework {
  static u32 _hook_bak[2];

  void TextEditorImpl::_KbdImpl_RenderTop_hook(void*) {
    asm volatile ("push {r5}");

    auto& te = *TextEditor::get_instance()->impl;
    auto const& screen = OSD::GetTopScreen();
    
    te.draw(screen);

    asm volatile ("pop {r5}");
  }

  void TextEditorImpl::_hook_init() {

    u32* ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv;
    memcpy(_hook_bak, ptr, sizeof(_hook_bak));

    ptr[0] = 0xE51FF004;  // ldr pc, [pc, #-4]
    ptr[1] = (u32)&TextEditorImpl::_KbdImpl_RenderTop_hook;

    ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl3RunEv;
    ptr[117] = 0xEA00000B;

    ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv;
    ptr[199] = 0xE28FF008;
    ptr[339] |= 1;
  }

  void TextEditorImpl::_hook_reset() {

    u32* ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv;
    memcpy(ptr, _hook_bak, sizeof(_hook_bak));
    
    ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl3RunEv;
    ptr[117] = 0x0A00000B;

    ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv;
    ptr[199] = 0xE350000A;
    *(u8*)(ptr + 339) = 0;
  }

  void TextEditorImpl::keyboardEvent(Keyboard& kbd, KeyboardEvent& ev) {
    auto& editor = *TextEditor::get_instance()->impl;

    switch( ev.type ) {
      case KeyboardEvent::CharacterAdded: {
        auto ch = kbd.GetInput()[0];

        if( ch == 0xA ) {
          editor.insert_newline();
        }
        else {
          editor.insert_char(kbd.GetInput()[0]);
        }

        break;
      }

      case KeyboardEvent::CharacterRemoved:
        editor.delete_char();
        break;

      case KeyboardEvent::KeyPressed:
      case KeyboardEvent::KeyDown:
      case KeyboardEvent::KeyReleased:
        editor.control(ev.type, ev.affectedKey);
        break;
    }

    kbd.GetInput().clear();
  }

  int TextEditorImpl::open() {
    Keyboard kbd;

    kbd.DisplayTopScreen = true;

    kbd.OnKeyboardEvent(keyboardEvent);

    _hook_init();

    std::string s;
    kbd.Open(s);

    _hook_reset();

    return 0;
  }

  void TextEditorImpl::update() {

  }

}