#include "CTRPluginFramework/System/Touch.hpp"

#include "3ds.h"
#include "CTRPluginFramework/System/Controller.hpp"
#include "types.h"

namespace CTRPluginFramework {
bool Touch::IsDown(void) { return (Controller::GetKeysDown() & Key::Touchpad); }

UIntVector Touch::GetPosition(void)
{
  touchPosition tp;

  hidTouchRead(&tp);
  return (UIntVector(tp.px, tp.py));
}
}  // namespace CTRPluginFramework
