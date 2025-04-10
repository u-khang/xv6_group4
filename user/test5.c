#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

#define NUM_PROCESSES 3

int main() {
    // Step 1: Give the parent the highest priority (0) so it can preempt children
    setpriority(getpid(), 0);

    int pids[NUM_PROCESSES];
    // Child A: priority 1, Child B: priority 2, Child C: priority 3
    int childPriorities[NUM_PROCESSES] = {1, 2, 3};

    // Step 2: Fork children
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int pid = fork();
        if (pid == 0) {
            // Child sets its own priority
            setpriority(getpid(), childPriorities[i]);

            // Large CPU loop so the parent has time to run in the middle
            for (volatile long j = 0; j < 500000000; j++);

            exit(0);
        } else {
            pids[i] = pid;
        }
    }

    // Step 3: Let the children start; parent will be scheduled often (priority 0)
    // We do a small sleep so Child A can begin, but the parent will still preempt it.
    sleep(5);

    // Step 4: Change Child C (index 2) from priority 3 to 0 *while it’s running*
    // Because the parent is priority 0, it WILL get scheduled in the middle.
    printf("Parent (priority 0): Changing Process %d from priority 3 to 0\n", pids[2]);
    setpriority(pids[2], 0);

    // Step 5: Wait for all children
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int finished_pid = wait(0);
        printf("Parent: Process %d finished.\n", finished_pid);
    }

    printf("Test Dynamic Priority Change Completed.\n");
    exit(0);
}

