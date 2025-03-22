
#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

#define NUM_PROCESSES 4

int main() {
    int pids[NUM_PROCESSES];
    int priorities[NUM_PROCESSES] = {1, 3, 3, 3}; // Process 1 (High), others (Same)

    // Fork all processes first
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int pid = fork();
        if (pid == 0) {
            // Child process: Simulate work
            for (volatile int j = 0; j < 100000000; j++); // Simulated CPU work
            exit(0);
        } else {
            pids[i] = pid; // Store child PIDs
        }
    }

    // Update priorities **after all processes are created**
    for (int i = 0; i < NUM_PROCESSES; i++) {
        setpriority(pids[i], priorities[i]); // Change priority
        printf("Parent changed Process %d priority to %d\n", pids[i], priorities[i]);
    }

    // Parent waits and prints finishing order
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int finished_pid = wait(0);
        printf("Process %d finished.\n", finished_pid);
    }

    printf("Test High-Priority First & Round-Robin Completed.\n");
    exit(0);
}

