#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"
#include "../Hotkeys.h"

namespace CTRPluginFramework {
  TextEditor::Result TextEditorImpl::open() {
    Keyboard kbd;

    kbd.DisplayTopScreen = true;

    kbd.OnKeyboardEvent(keyboardEvent);

    do {
      Controller::Update();
    } while ( Controller::GetKeysDown() );

    _hook_init();

    std::string s;
    kbd.Open(s);

    _hook_reset();

    if( saved ) {
      return TextEditor::Result::Saved;
    }

    return TextEditor::Result::Canceled;
  }


}