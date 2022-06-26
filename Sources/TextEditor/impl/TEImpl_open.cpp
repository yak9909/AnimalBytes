#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"
#include "../Hotkeys.h"

namespace CTRPluginFramework {
  TextEditor::Result TextEditorImpl::open() {
    Keyboard kbd;

    kbd.DisplayTopScreen = false;
    kbd.DontReturnAfterEnter = true;
    kbd.MakeEventOfSpace = true;
    kbd.ForceMakeEventOfBackspace = true;

    kbd.TopScreenRenderer = [] (Keyboard& kbd, Screen const& screen) -> void {
      auto& inst = *TextEditor::get_instance()->impl;

      inst.draw(screen);
    };

    kbd.BottomScreenRenderer = [] (Keyboard& kbd, Screen const& screen) -> void {
      auto& inst = *TextEditor::get_instance()->impl;

      inst.draw_bottom(screen);
    };

    kbd.OnKeyboardEvent(keyboardEvent);

    do {
      Controller::Update();
    } while ( Controller::GetKeysDown() );

    std::string s;
    kbd.Open(s);

    if( saved ) {
      return TextEditor::Result::Saved;
    }

    return TextEditor::Result::Canceled;
  }


}