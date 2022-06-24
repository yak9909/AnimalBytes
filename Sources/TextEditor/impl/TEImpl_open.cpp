#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
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
  static u32 _hook_bak[2];

  void TextEditorImpl::_KbdImpl_RenderTop_hook(void*) {
    asm volatile ("push {r5}");

    auto& te = *TextEditor::get_instance()->impl;
    auto const& screen = OSD::GetTopScreen();
    
    te.draw(screen);

    asm volatile ("pop {r5}");
  }

  void TextEditorImpl::_KbdImpl_RenderBottom_hook(void*) {
    
    auto& te = *TextEditor::get_instance()->impl;
    auto const& screen = OSD::GetBottomScreen();

    te.draw_bottom(screen);

  }

  void TextEditorImpl::_hook_init() {

    u32* ptr = (u32*)&_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv;
    memcpy(_hook_bak, ptr, sizeof(_hook_bak));

    constexpr u32 asmjmp = 0xE51FF004; // ldr pc, [pc, #-4]

    ptr[0] = asmjmp;
    ptr[1] = (u32)TextEditorImpl::_KbdImpl_RenderTop_hook;

    ptr = (u32*)_ZN18CTRPluginFramework12KeyboardImpl3RunEv;
    ptr[117] = 0xEA00000B;

    ptr = (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv;
    ptr[199] = 0xE28FF008; // new line
    ptr[203] = calc_branch_offset((u32)ptr + 0x32C, (u32)ptr + 0x32C + 0x54);
    ptr[339] |= 1;

    ptr = (u32*)_ZN18CTRPluginFramework12KeyboardImpl13_RenderBottomEv;
    ptr[134] = asmjmp;
    ptr[135] = (u32)_hookHelperFn_KbdImpl_RenderBottom;
  }

  void TextEditorImpl::_hook_reset() {

    u32* ptr = (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_RenderTopEv;
    memcpy(ptr, _hook_bak, sizeof(_hook_bak));
    
    ptr = (u32*)_ZN18CTRPluginFramework12KeyboardImpl3RunEv;
    ptr[117] = 0x0A00000B;

    ptr = (u32*)_ZN18CTRPluginFramework12KeyboardImpl10_CheckKeysEv;
    ptr[199] = 0xE350000A; // new line
    ptr[203] = 0xE3700005;
    *(u8*)(ptr + 339) = 0;

    ptr = (u32*)_ZN18CTRPluginFramework12KeyboardImpl13_RenderBottomEv;
    ptr[134] = 0xE28DD024;
    ptr[135] = 0xE8BD80F0;
  }

  int TextEditorImpl::open() {
    Keyboard kbd;

    kbd.DisplayTopScreen = true;

    kbd.OnKeyboardEvent(keyboardEvent);

    do {
      Controller::Update();
    } while ( Controller::GetKeysDown() );

    _hook_init();

    std::string s;
    kbd.Open(s);

    _hook_reset();

    return 0;
  }

  void TextEditorImpl::update() {

  }

}