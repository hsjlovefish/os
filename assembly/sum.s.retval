.text
.code16
.global sum
sum:
  push %bp
  mov %sp, %bp
  sub $2, %sp

  mov $1, %bx
  mov $0, -2(%bp)
1:
  add %bx, -2(%bp)
  inc %bx
  cmp 4(%bp), %bx
  jbe 1b

  mov -2(%bp), %ax

  mov %bp, %sp
  pop %bp
  ret
