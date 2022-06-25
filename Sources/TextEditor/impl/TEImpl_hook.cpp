#include <CTRPluginFramework.hpp>
#include "TEImpl.h"
#include "../Hotkeys.h"

#define  calc_branch_offset(From, To)  (((((To) - (From)) >> 2) - 2) & 0xFFFFFF)

extern "C" {
  void _ZN18CTRPluginFramework12KeyboardImpl3RunEv(void*);
  void _ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv(void*);
  void _ZN18CTRPluginFramework12KeyboardImpl13_RenderBottomEv(void*);
  void _ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv(void*);

  void _hookHelperFn_KbdImpl_RenderBottom();
};

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

    constexpr u32 asmjmp = 0xE51FF004; // ldr pc, [pc, #-4]

    std::pair<u32*, u32> const hookMap[] {
      // Don't return with KEY_ENTER
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl3RunEv + 117, 0xEA00000B },

      // Allow space key
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 203,
          (0xEA << 24) | calc_branch_offset((u32)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 0x32C,
            (u32)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv + 0x380) },
      
      // Draw editor
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv, asmjmp },
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv + 1, (u32)TextEditorImpl::_KbdImpl_RenderTop_hook },

      // bottom
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl13_RenderBottomEv + 134, asmjmp },
      { (u32*)_ZN18CTRPluginFramework12KeyboardImpl13_RenderBottomEv + 135, (u32)_hookHelperFn_KbdImpl_RenderBottom },
    };

    for( auto&& item : hookMap ) {
      _hook_bak.emplace_back(item.first, *item.first);
      *item.first = item.second;
    }
  }

  void TextEditorImpl::_hook_reset() {
    for( auto&& item : _hook_bak ) {
      *item.first = item.second;
    }

    _hook_bak.clear();
  }
}