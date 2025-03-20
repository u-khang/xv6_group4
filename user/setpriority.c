#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUM_PROCS 5

int main() {
    int priorities[NUM_PROCS] = {3, 1, 4, 2, 0};  // Lower value = higher priority

    for (int i = 0; i < NUM_PROCS; i++) {
        int pid = fork();
        if (pid < 0) {
            exit(1);  // Exit silently if fork fails
        }
        if (pid == 0) {  // Child process
            setpriority(getpid(),priorities[i]);
            
            // Simulate workload
            for (int j = 0; j < 5; j++) {
                  // Small delay to simulate execution
                  sleep(10);
            }
            
            exit(0);
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < NUM_PROCS; i++) {
        wait(0);
    }

    exit(0);
}
