#pragma once

namespace CTRPluginFramework::Cheats {
  class CodeContext {
  public:
    struct EnabledFlags {
      bool CoordMod   = false;
    };

    EnabledFlags flags;

    static CodeContext* get_instance();

  private:
    CodeContext();
  };
}