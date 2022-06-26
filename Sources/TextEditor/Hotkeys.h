#pragma once

#include <CTRPluginFramework.hpp>
#include "types.h"

namespace CTRPluginFramework::Hotkeys {
  constexpr u32
    CursorUp    = DPadUp,
    CursorDown  = DPadDown,
    CursorLeft  = DPadLeft,
    CursorRight = DPadRight,

    // Circle Pad
    ScreenUp    = CPadUp,
    ScreenDown  = CPadDown,
    ScreenLeft  = CPadLeft,
    ScreenRight = CPadRight,

    // Submenu
    Submenu     = Key::Start,

    // Insert a new empty line
    InsertNewLineBase   = Key::L,
    InsertToForward     = DPadUp,
    InsertToBackward    = DPadDown,

    // Select
    Selecting       = Key::X,
    
    // Copy and Paste
    CopyPasteBase   = Key::R,
    Copy            = DPadLeft,
    Paste           = DPadRight,

    // General
    Enter       = Key::A,
    Backspace   = Key::Y,

    // Debug
    DBG_ShowLine0addr = Key::L

    ;
}
