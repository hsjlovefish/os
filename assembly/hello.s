.text
.code16
start:
  mov $stack, %sp
  mov %sp, %bp
  sub $2, %sp

  push $11
  call sum

  mov %ax, -2(%bp)
  add $2, %sp

  mov $0x3f8, %dx
  out %ax, %dx
  hlt

.org 0x1000
stack:
