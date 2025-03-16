#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: setpriority <priority>\n");
    exit(1);
  }

  int priority = atoi(argv[1]);
  int pid = forkP(priority);

  if (pid < 0) {
    printf("forkP failed\n");
  } else if (pid == 0) {
    printf("Child process with priority %d\n", priority);
  } else {
    printf("Parent process created child %d with priority %d\n", pid, priority);
  }

  exit(0);
}
