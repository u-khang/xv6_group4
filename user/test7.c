// file: test_invalid_priority.c
#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main() {
  int pid = getpid();
  // Try setting priority to 99, which is invalid
  int ret = setpriority(pid, 99);

  if (ret < 0) {
    printf("Passed: setpriority(%d, 99) returned error as expected.\n", pid);
  } else {
    printf("Failed: setpriority(%d, 99) did NOT return error!\n", pid);
  }

  exit(0);
}

