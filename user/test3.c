#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main() {
  int priorities[3] = {1, 2, 3}; // lower number = higher priority

  for (int i = 0; i < 3; i++) {
    int pid = fork();
    if (pid == 0) {
      setpriority(getpid(), priorities[i]);
      for (volatile int j = 0; j < 100000000; j++); // simulate work
      exit(0);
    }
  }

  for (int i = 0; i < 3; i++) {
    int finished_pid = wait(0);
    printf("Process %d finished.\n", finished_pid);
  }

  printf("Test Mixed Priorities completed.\n");
  exit(0);
}

