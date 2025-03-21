#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define LOOP_ITERATIONS 1000000000  // Each child runs this many iterations

void finite_process(int priority) {
    setpriority(getpid(), priority);  // Set priority for the child process
    printf("Child process %d started with priority %d\n", getpid(), priority);
    sleep(10);
    volatile int x = 0;  // Make sure each process has its own variable
    for (int j = 0; j < LOOP_ITERATIONS; j++) {  
        x += j;  // Independent computation to keep CPU busy
    }

    printf("Child process %d with priority %d completed execution\n", getpid(), priority);
    exit(0);
}

int main() {
    setpriority(getpid(), 0);  // Set the parent process priority to 0

    for (int i = 4; i > 0; i--) {  // Create 4 child processes with different priorities
        int pid = fork();
        if (pid == 0) {
            // Child process runs its own independent computation
            finite_process(i);
        } else if (pid > 0) {
            // Parent prints message when a child is created
            printf("Created child process %d with priority %d\n", pid, i);
        } else {
            // Fork failed
            printf("Failed to create process\n");
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < 4; i++) {
        wait(0);
    }

    printf("All child processes have completed\n");
    exit(0);
}
