#include "app/libc/print.h"
#include "app/libc/std.h"
#include "app/libc/type.h"

int main() {
  while (1) {
    print('B');
    sleep(1000);
  }
}