#include "include/mm.h"
#include "include/print.h"
#include "include/sched.h"
#include "include/segment.h"
#include "include/string.h"
#include "include/tss.h"

static struct task* task_head;
static struct task* task_tail;
struct task* current;

static void fake_task_stack(unsigned long kstack) {
  uint16_t ss = USER_DS;
  unsigned long rsp = 0x8000000;
  uint16_t cs = USER_CS;
  unsigned long rip = 0x100000;
  unsigned long rsp_tmp;

  __asm__ ("mov %%rsp, %5\n\t"
           "mov %4, %%rsp\n\t"
           "pushq %0\n\t"
           "pushq %1\n\t"
           "pushf\n\t"
           "pushq %2\n\t"
           "pushq %3\n\t"
           "mov %5, %%rsp\n\t"
           :
           : "m"(ss), "m"(rsp), "m"(cs), "m"(rip), "m"(kstack), "m"(rsp_tmp));
}

static void make_task(unsigned long id, unsigned long entry, unsigned long entry_pa) {
  struct task* task = malloc(sizeof(struct task));
  task->id = id;
  task->state = TASK_RUNNING;

  task->pml4 = alloc_page();
  memset(VA(task->pml4), 0, PAGE_SIZE);

  memcpy(VA(task->pml4 + 8 * 256), VA(TASK0_PML4 + 8 * 256), 8 * 256);
  map_range(task->pml4, entry, entry_pa, 0x4, 1024);

  task->kstack = (unsigned long)VA(alloc_page()) + PAGE_SIZE;
  
  fake_task_stack(task->kstack);
  task->rsp0 = task->kstack - 8 * 5;
  task->rip = (unsigned long)&ret_from_kernel;

  if (!task_head) {
    task_head = task;
    task_tail = task;
    task->prev = NULL;
    task->next = NULL;
  } else {
    task_tail->next = task;
    task->prev = task_tail;
    task->next = NULL;
    task_tail = task;
  }
}

void sched_init() {
  make_task(1, 0x100000, 0xc800000);

  current = task_head; 
}

void do_timer() {
  print('T');
}