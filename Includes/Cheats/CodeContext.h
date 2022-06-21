#pragma once

namespace CTRPluginFramework::Cheats {
  class CodeContext {
  public:
    struct EnabledFlags {
      bool f_coordmod   = 0;
      bool f_autodrop   = 0;


    };

    struct CAutoDrop {
      u32 item;
      int hotkey_held_time;
      bool view_item_id;

    };

    EnabledFlags enabled_flags;
    CAutoDrop c_autodrop;

    void fill_zero();

    static CodeContext* get_instance();

  private:
    CodeContext() = delete;
    CodeContext(CodeContext const&) = default;
  };
}