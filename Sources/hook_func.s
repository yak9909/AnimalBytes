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
	push {r4-r7, lr}  @
	mov r5, r3        @ original op
	ldr ip, .L_return_to
  add ip, #8
  bx ip
.L_return_to:
	.word _ZN18CTRPluginFramework7OSDImpl10OSDMessageC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ColorESC_
.L_elemdeleter:
  .word _hookFnHelper_OSDMessageElementDeleter_
