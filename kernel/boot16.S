.text
.code16
start16:
  cli

  lgdt gdtr

  mov %cr0, %eax
  or $0x1, %eax
  mov %eax, %cr0

  ljmpl $0x8, $0x20000

gdt:
  .quad 0x0000000000000000
  .quad 0x00c09a00000007ff
  .quad 0x00c09200000007ff
gdt_end:

gdtr:
  .word gdt_end - gdt
  .word gdt, 0x1
