#define IO_PIC     0x20
#define IRQ_OFFSET 32

.text
.code16
start16:
  cli

  # read E820
  mov $e820_entry, %di
  xor %ebx, %ebx
e820_rd_entry:
  mov $0xe820, %eax
  mov $20, %ecx
  int $0x15

  add $20, %di
  incb e820_nr_entry

  cmp $0, %ebx
  jne e820_rd_entry

  # Init 8259A
  mov $0x13, %al
  mov $(IO_PIC), %dx
  out %al,%dx
  # ICW2
  mov $(IRQ_OFFSET), %al
  mov $(IO_PIC+1), %dx
  out %al, %dx
  # ICW4
  mov $0x1, %al
  mov $(IO_PIC+1), %dx
  out %al, %dx

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

.org 0x3000
e820_nr_entry:
  .long 0
e820_entry:
  .fill 1024, 1, 0
