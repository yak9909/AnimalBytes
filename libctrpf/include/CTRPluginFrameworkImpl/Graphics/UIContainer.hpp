#ifndef CTRPLUGINFRAMEWORKIMPL_UICONTAINER_HPP
#define CTRPLUGINFRAMEWORKIMPL_UICONTAINER_HPP

#include <vector>

#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"

namespace CTRPluginFramework {
class UIContainer {
 public:
  UIContainer(void);
  ~UIContainer(void);

  void operator+=(Drawable *uiControl);
  void Draw(void);
  void Update(const bool isTouchDown, const IntVector &touchPos);
  void ExecuteAll(void);

 private:
  std::vector<Drawable *> _uiControls;
};
}  // namespace CTRPluginFramework

#endif
