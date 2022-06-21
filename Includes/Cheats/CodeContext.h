#pragma once

namespace CTRPluginFramework::Cheats {
  class CodeContext {
  public:
    struct EnabledFlags {
      bool f_coordmod   = 0;
      bool f_autodrop   = 0;

    };

    struct DropCheats {
      u32 item;
      u8 type;

      bool drop(u8 wx, u8 wy);
    };

    // struct CItemChanger {
    //   int hotkey_held_tick;
    // };

    struct CAutoDrop {
      bool view_item_id;
    };

    EnabledFlags enabled_flags;
    DropCheats c_dropcheats;
    CAutoDrop c_autodrop;

    void init();

    static CodeContext* get_instance();

  private:
    CodeContext() = delete;
    CodeContext(CodeContext const&) = default;
  };
}