#ifndef CTRPLUGINFRAMEWORKIMPL_COMBOBOX_HPP
#define CTRPLUGINFRAMEWORKIMPL_COMBOBOX_HPP

#include <string>
#include <vector>

#include "CTRPluginFramework/System/Rect.hpp"
#include "CTRPluginFramework/System/Vector.hpp"
#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"

namespace CTRPluginFramework {
class ComboBox : public Drawable {
 public:
  ComboBox(int posX, int posY, int width, int height);

  void Add(const std::string &item);
  void Clear(void);
  void Draw(void) override;
  void Update(const bool isTouchDown, const IntVector &touchPos) override;
  bool operator()(void) override;

  bool IsEnabled;
  bool IsVisible;
  int SelectedItem;

 private:
  bool _execute;
  bool _isTouched;
  IntRect _rectPos;
  std::vector<std::string> _items;
};
}  // namespace CTRPluginFramework

#endif