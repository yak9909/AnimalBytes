#ifndef CTRPLUGINFRAMEWORKIMPL_PLUGINMENUHOTKEYS_HPP
#define CTRPLUGINFRAMEWORKIMPL_PLUGINMENUHOTKEYS_HPP

#include <string>
#include <vector>

#include "CTRPluginFrameworkImpl/Graphics/Button.hpp"

namespace CTRPluginFramework {
class HotkeysModifier {
 public:
  HotkeysModifier(u32 &keys, const std::string &message);
  ~HotkeysModifier(void);

  void operator()(void);

 private:
  void _DrawTop(void) const;
  void _DrawBottom(void);
  void _Update(void);

  u32 &_keys;
  std::vector<Button> _checkboxs;
  const std::string _message;
};
}  // namespace CTRPluginFramework

#endif