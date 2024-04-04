#include "include/mm.h"
#include "include/print.h"
#include "include/segment.h"

int main() {
  // enter the main
  __asm__("mov $0x3f8, %dx\n\t"
         "mov $'M', %ax\n\t"
         "out %ax, %dx\n");

  mm_init();

  // test whether physical memory mapping is successful
  // unsigned long* x = VA(200 * 1024 * 1024);
  // *x = 5;
  // print(*x);

  __asm__("hlt");
}
