#include "include/types.h"
#include "include/mm.h"

unsigned long alloc_page() {
  unsigned long addr = 0;

  for (long i = KERNEL_PAGE_NUM; i < mem_size / PAGE_SIZE; i++) {
    if (pages[i] == 0) {
      pages[i] = 1;
      addr = PAGE_SIZE * i;
      break;
    }
  }

  return addr;
}

void free_page(unsigned long addr) {
  long index = addr / PAGE_SIZE;

  pages[index] = 0;  
}
