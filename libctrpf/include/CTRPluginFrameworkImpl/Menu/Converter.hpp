#ifndef CTRPLUGINFRAMEWORKIMPL_CONVERTER_HPP
#define CTRPLUGINFRAMEWORKIMPL_CONVERTER_HPP

#include "CTRPluginFrameworkImpl/Graphics/NumericTextBox.hpp"
#include "types.h"

namespace CTRPluginFramework {
class Converter {
 public:
  Converter(void);
  ~Converter(void);

  // Blocking call
  void operator()(u32 val = 0);

  static Converter *Instance(void);

 private:
  NumericTextBox _decimalTB;
  NumericTextBox _hexadecimalTB;
  NumericTextBox _floatTB;
  NumericTextBox _hexfloatTB;

  void _Draw(void);
};
}  // namespace CTRPluginFramework

#endif
