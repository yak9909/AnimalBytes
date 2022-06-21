#pragma once

namespace CTRPluginFramework::Cheats {
  class CodeContext {
  public:
    struct EnabledFlags {
      bool CoordMod   = 0;
      bool AutoDrop   = 0;


    };

    EnabledFlags flags;

    

    static CodeContext* get_instance();

  private:
    CodeContext();
  };
}