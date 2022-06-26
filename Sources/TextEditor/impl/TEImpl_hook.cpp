#include <CTRPluginFramework.hpp>
#include "TEImpl.h"
#include "../Hotkeys.h"

#define  calc_branch_offset(From, To)  (((((To) - (From)) >> 2) - 2) & 0xFFFFFF)

namespace CTRPluginFramework {
  static std::vector<std::pair<u32*, u32>> _hook_bak;

  void TextEditorImpl::_KbdImpl_RenderTop_hook(void*) {
    auto& te = *TextEditor::get_instance()->impl;
    auto const& screen = OSD::GetTopScreen();
    
    te.draw(screen);
  }

  void TextEditorImpl::_KbdImpl_RenderBottom_hook(void*) {
    auto& te = *TextEditor::get_instance()->impl;
    auto const& screen = OSD::GetBottomScreen();

    te.draw_bottom(screen);
  }

  void TextEditorImpl::_hook_init() {

    constexpr u32 asmjmp = 0xE51FF004;
    constexpr u32 asmNop = 0xE1A00000;

    constexpr u32 asmLoadAddr = 0xE59FC000; // ldr ip, [pc]
    constexpr u32 asmJumpIP   = 0xE12FFF1C; // bx ip

    std::pair<u32*, u32> const hookMap[] {
      // Don't return with KEY_ENTER
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl3RunEv + 117, 0xEA00000B },

      // Space key
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 203, asmNop },
      
      // Enter
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 199, 0xE28FF008 },

      // Backspace
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 339, 0xE3550001 },

      // Draw editor
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv, asmjmp },
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv + 1, (u32)TextEditorImpl::_KbdImpl_RenderTop_hook },

      // bottom
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl13_RenderBottomEv + 134, asmjmp },
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl13_RenderBottomEv + 135, (u32)_hookHelperFn_KbdImpl_RenderBottom },
    };

    if( _hook_bak.empty() ) {
      for( auto&& item : hookMap ) {
        _hook_bak.emplace_back(item.first, *item.first);
      }
    }

    for( auto&& item : hookMap ) {
      *item.first = item.second;
    }
  }

  void TextEditorImpl::_hook_reset() {
    for( auto&& item : _hook_bak ) {
      *item.first = item.second;
    }
  }
}