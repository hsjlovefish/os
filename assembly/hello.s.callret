.text
.code16
start:
  mov $stack, %sp
  call sum

  mov $0x3f8, %dx
  mov $0x41, %al
  out %al, %dx
  hlt

sum:
  mov $1, %bx
  mov $0, %ax
1:
  add %bx, %ax
  inc %bx
  cmp $10, %bx
  jbe 1b

  mov $0x3f8, %dx
  out %ax, %dx
  ret

.org 0x1000
stack:
