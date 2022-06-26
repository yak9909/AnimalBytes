#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"
#include "../Hotkeys.h"

namespace CTRPluginFramework {
  void TextEditorImpl::keyboardEvent(Keyboard& kbd, KeyboardEvent& ev) {
    auto& editor = *TextEditor::get_instance()->impl;

    switch( ev.type ) {
      case KeyboardEvent::CharacterAdded: {
        auto ch = kbd.GetInput()[0];

        if( ch == 0xA ) {
          editor.newline();
        }
        else if( ch == 0 ) {
          editor.insert_char(' ');
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
        if( ev.affectedKey == Hotkeys::Submenu ) {
            
          //_hook_reset();
          
          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv) = 0xE92D4030;
          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv + 1) = 0xE59F5168;
          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl3RunEv + 117) = 0x0A00000B;
          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 199) = 0xE350000A;

          editor.submenu_open(OSD::GetTopScreen());

          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv) = 0xE51FF004;
          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv + 1) = (u32)TextEditorImpl::_KbdImpl_RenderTop_hook;
          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl3RunEv + 117) = 0xEA00000B;
          *((u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 199) = 0xE28FF008;

          //*((u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 199) = 0xE28FF008;
          //_hook_init();

          break;
        }

      case KeyboardEvent::KeyDown:
      case KeyboardEvent::KeyReleased:
        editor.control(ev.type, ev.affectedKey);
        break;
    }

    kbd.GetInput().clear();
  }
}