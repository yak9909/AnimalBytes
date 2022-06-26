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

        if( ch == ' ' ) {
          editor.insert_char(' ');
        }
        else {
          editor.insert_char(kbd.GetInput()[0]);
        }

        break;
      }

      case KeyboardEvent::BackspacePressed:
        editor.delete_char();
        break;

      case KeyboardEvent::EnterPressed:
        editor.newline();
        break;

      case KeyboardEvent::KeyPressed:
        if( ev.affectedKey == Hotkeys::Submenu ) {
          editor.submenu_open(OSD::GetTopScreen());
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