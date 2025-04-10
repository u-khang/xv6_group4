#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void workload() {
  for (volatile int i = 0; i < 100000000; i++); // Simulate workload
}

int main() {
  int pid1, pid2, pid3;

  pid1 = fork();
  if (pid1 == 0) {
    setpriority(getpid(), 4); // Highest priority
    workload();
    sleep(100);
    printf("TEST: Process %d (priority 4) finished\n", getpid());
    exit(0);
  }

  pid2 = fork();
  if (pid2 == 0) {
    setpriority(getpid(), 0); // Medium priority
    workload();
    sleep(100);
    printf("TEST: Process %d (priority 0) finished\n", getpid());
    exit(0);
  }

  pid3 = fork();
  if (pid3 == 0) {
    setpriority(getpid(), 2); // Lowest priority
    workload();
    sleep(100);
    printf("TEST: Process %d (priority 2) finished\n", getpid());
    exit(0);
  }

  wait(0);
  wait(0);
  wait(0);
  exit(0);
}
