.text
.code64
1:
  # page fault
  movb $'F', (0x12345678)
  mov (0x12345678), %al

  mov $0x3f8, %dx
  out %al, %dx

  jmp 1b