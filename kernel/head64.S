#include "include/segment.h"

.text
.code64
  mov $0x3f8, %dx
  mov $'L', %ax
  out %ax, %dx

  lgdt gdtr

  mov $KERNEL_DS, %ax
  mov %ax, %ds
  mov %ax, %ss
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs

  # setup stack
  mov $task0_stack, %rsp

  push $main
  ret

.align 64
gdt:
  .quad 0x0000000000000000  /* reserved */
  .quad 0x00209a0000000000  /* kernel cs */
  .quad 0x0000920000000000  /* kernel ds */
  .quad 0x0000000000000000  /* user32 cs */
  .quad 0x0000f20000000000  /* user ds */
  .quad 0x0020fa0000000000  /* user64 cs */
  .fill 64 - 6, 8, 0
gdt_end:

gdtr:
  .word gdt_end - gdt
  .quad gdt

# 4kb
.fill 4096, 1, 0
task0_stack:
