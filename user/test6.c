#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main() {
    // Give the parent the same priority as Child A (1),
    // so the parent can actually run mid-execution.
    setpriority(getpid(), 1);

    int pids[2];
    // Child A: priority 1, Child B: priority 2
    int childPriorities[2] = {1, 2};

    // Fork 2 children
    for (int i = 0; i < 2; i++) {
        int pid = fork();
        if (pid == 0) {
            // Child sets its own priority
            setpriority(getpid(), childPriorities[i]);

            // Large CPU loop so the parent has time to run mid-execution
            for (volatile long j = 0; j < 500000000; j++);

            // Done
            exit(0);
        } else {
            pids[i] = pid;
        }
    }

    // Sleep a bit so Child A (priority 1) starts running,
    // but the parent also has priority 1, so it will preempt Child A occasionally.
    sleep(5);

    // Now lower Child A’s priority from 1 to 2
    // so it matches Child B (also priority 2).
    printf("Parent: Changing Child A (pid=%d) priority from 1 to 2\n", pids[0]);
    setpriority(pids[0], 2);

    // Wait for both children, printing their completion order
    for (int i = 0; i < 2; i++) {
        int finished_pid = wait(0);
        printf("Parent: Child %d finished.\n", finished_pid);
    }

    printf("Test Dynamic + Round-Robin Completed.\n");
    exit(0);
}

