#include "app/libc/print.h"
#include "app/libc/std.h"
#include "app/libc/type.h"

int main() {
  void* shm = shm_open("shm");
  *(char*)shm = 'S';

  while (1) {
    print('A');
    sleep(1000);
  }
}
