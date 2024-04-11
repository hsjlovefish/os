#include "include/mm.h"
#include "include/print.h"
#include "include/string.h"
#include "include/sched.h"
#include "include/types.h"

unsigned long mem_size = 0;
char pages[MAX_PAGES];

void map_range(unsigned long pml4_pa, unsigned long from_va, unsigned long to_pa, char us, long npage);

void mm_init() {
  struct e820map* e820 = (struct e820map*)0x13000;

  for (int i = 0; i < e820->nr_entry; i++) {
    if (e820->map[i].type == E820_RAM) {
      unsigned long tmp = e820->map[i].addr + e820->map[i].size;
      if (tmp > mem_size) {
        mem_size = tmp;
      }
    }
  }

  print(mem_size);

  memset(pages, 0, MAX_PAGES);

  for (int i = 0; i < KERNEL_PAGE_NUM; i++) {
    pages[i] = 1;
  }

  map_range(TASK0_PML4, (unsigned long)VA(0), 0, 0, (mem_size + PAGE_SIZE - 1) / PAGE_SIZE);
}

void map_range(unsigned long pml4_pa, unsigned long from_va, unsigned long to_pa, char us, long npage) {
  long n = 0;
    
  while (n < npage) {
  	// pml4
  	unsigned long* page_va = VA(pml4_pa);
  	short index = (from_va >> 39) & 0x1ff;
  	unsigned long entry = *(page_va + index);
  	if (!(entry & 0x1)) {
      *(page_va + index) = alloc_page() | 0x3 | us;
      entry = *(page_va + index);
  	}

  	// pml3
  	page_va = VA(entry & 0xffffffffff000);
  	index = (from_va >> 30) & 0x1ff;
  	entry = *(page_va + index);
  	if (!(entry & 0x1)) {
      *(page_va + index) = alloc_page() | 0x3 | us;
      entry = *(page_va + index);
  	}

  	// pml2
  	page_va = VA(entry & 0xffffffffff000);
  	index = (from_va >> 21) & 0x1ff;
  	entry = *(page_va + index);
  	if (!(entry & 0x1)) {
      *(page_va + index) = alloc_page() | 0x3 | us;
      entry = *(page_va + index);
  	}

  	// pml1
  	page_va = VA(entry & 0xffffffffff000);
  	index = (from_va >> 12) & 0x1ff;
  	if (!((*(page_va + index)) & 0x1)) {
      *(page_va + index) = (to_pa + PAGE_SIZE * n) | 0x3 | us;
  	}
		
    n++;
    from_va += PAGE_SIZE;
  }
}

void do_page_fault(unsigned long addr) {
  unsigned long pa = alloc_page();
  map_range(current->pml4, addr, pa, 0x4, 1);
}