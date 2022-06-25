.arm
.align 4

  .section .text
  .global _hookFn_OSDMessage_ctor
  .type _hookFn_OSDMessage_ctor, %function
_hookFn_OSDMessage_ctor:
  push {r0-r7, lr}
  ldr ip, .L_elemdeleter
  mov lr, pc
  bx ip
  pop {r0-r7, lr}
  push {r4-r7, lr}       @
  mov r5, r3             @ original op
  ldr ip, .L_return_to
  bx ip
.L_return_to:
  .word _ZN18CTRPluginFramework7OSDImpl10OSDMessageC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ColorESC_ + 8
.L_elemdeleter:
  .word _hookFnHelper_OSDMessageElementDeleter_

  .section .text
  .global _hookHelperFn_KbdImpl_RenderBottom
  .type _hookHelperFn_KbdImpl_RenderBottom, %function
_hookHelperFn_KbdImpl_RenderBottom:
  add sp, #0x24
  pop {r4-r7, lr}
  push {lr}
  mov lr ,pc
  ldr pc, .L_RenderBottomHook
  pop {pc}

.L_RenderBottomHook:
  .word _ZN18CTRPluginFramework14TextEditorImpl26_KbdImpl_RenderBottom_hookEPv
