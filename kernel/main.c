#include "include/interrupt.h"
#include "include/mm.h"
#include "include/print.h"
#include "include/sched.h"
#include "include/segment.h"
#include "include/syscall.h"
#include "include/tss.h"

int main() {
  // enter the main
  __asm__("mov $0x3f8, %dx\n\t"
         "mov $'M', %ax\n\t"
         "out %ax, %dx\n");

  mm_init();
  interrupt_init();
  syscall_init(); 

  __asm__("sti");
  sched_init();
  tss_init();

  // test whether physical memory mapping is successful
  // unsigned long* x = VA(200 * 1024 * 1024);
  // *x = 5;
  // print(*x);

  __asm__ ("mov %0, %%cr3": :"r"(current->pml4));

  init_8254();

  __asm__ ("movq %0, %%rsp\n\t"
           "jmp ret_from_kernel\n\t"
           :
           : "m"(current->rsp0)
          );
}
