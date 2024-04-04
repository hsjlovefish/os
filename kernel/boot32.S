.text
.code32
start32:
  mov $0x3f8, %dx
  mov $'P', %al
  out %al, %dx

  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss

  lgdt gdtr

  # fill kmap level 2
  mov $0x32000, %edi
  mov $0x33000 + 3, %eax
1:
  stosl
  add $0x1000, %eax
  add $4, %edi

  cmp $(0x32000 + 31 * 8), %edi
  jle 1b

  # fill kmap level 1
  mov $0x33000, %edi
  mov $0x0 + 3, %eax
2:
  stosl
  add $0x1000, %eax
  add $4, %edi

  cmp $(0x33000 + 512 * 32 * 8 - 8), %edi
  jle 2b

  # setup direct-map level2
  mov $0x56000, %edi
  mov $0x33000 + 3, %eax
3:
  stosl
  add $0x1000, %eax
  add $4, %edi

  cmp $(0x56000 + 32 * 8 - 8), %edi
  jle 3b

  # enable PAE
  mov %cr4, %eax
  btsl $5, %eax
  movl %eax, %cr4

  # setup CR3
  movl $0x30000, %eax
  movl %eax, %cr3

  # setup EFER
  movl $0xc0000080, %ecx
  rdmsr
  # enable long mode
  btsl $8, %eax
  # enable syscall/sysret
  btsl $0, %eax
  wrmsr

  mov %cr0, %eax
  bts $31, %eax
  mov %eax, %cr0

  ljmp $0x8, $0x100000

gdt:
  .quad 0x0000000000000000
  .quad 0x00209a0000000000
  .quad 0x0000920000000000
gdt_end:

gdtr:
  .word gdt_end - gdt
  .long gdt

.org 0x10000
  .quad 0x0000000000053003
  .fill 272, 8, 0
  .quad 0x0000000000055003
  .fill 237, 8, 0
  .quad 0x0000000000031003

.org 0x11000
  .fill 510, 8, 0
  .quad 0x0000000000032003
  .fill 1, 8, 0

.org 0x12000
  .fill 512, 8, 0

.org 0x13000
  .fill 512 * 32, 8, 0

.org 0x33000
  .quad 0x0000000000054003
  .fill 511, 8, 0

.org 0x34000
  .quad 0x0000000000033003
  .fill 511, 8, 0

## linear map
# pml3
.org 0x35000
  .quad 0x0000000000056003
  .fill 511, 8, 0

# pml2
.org 0x36000
  .fill 32, 8, 0
  .quad 0x0000000000057003
  .fill 479, 8, 0

# pml1
.org 0x37000
  .fill 512, 8, 0
