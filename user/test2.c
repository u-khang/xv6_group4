#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

#define NUM_CHILDREN 3

int main() {
  for (int i = 0; i < NUM_CHILDREN; i++) {
    int pid = fork();
    if (pid == 0) {
      for (volatile int j = 0; j < 100000000; j++); // simulate CPU work
      exit(0); // No printf in child
    }
  }

  // Parent prints which child finished
  for (int i = 0; i < NUM_CHILDREN; i++) {
    int finished_pid = wait(0);
    printf("Child %d done\n", finished_pid);
  }

  printf("Test Round-Robin completed\n");
  exit(0);
}

