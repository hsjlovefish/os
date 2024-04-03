.text
.code32
start32:
  mov $0x3f8, %dx
  mov $'P', %al
  out %al, %dx

  hlt
