#pragma once

#include "types.h"

namespace CTRPluginFramework {
  enum Region {
    USA,
    EUR
  };

  class AutoRegion {
  public:
    // Constructor
    AutoRegion(u32 usa, u32 eur);
    ~AutoRegion(){}

    // Return the value according to the current region
    u32 operator()(void) const;

    // Properties
    const u32 Usa;
    const u32 Eur;
  };
}