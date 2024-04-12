#include "app/libc/print.h"
#include "app/libc/std.h"
#include "app/libc/type.h"

int main() {
  void* shm = shm_open("shm");

  while (1) {
    print(*(char*)shm);
    sleep(1000);
  }
}
