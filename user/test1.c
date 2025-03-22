#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child process: Check initial priority
        int mypid = getpid();
        printf("Child Process %d: Default Priority 4)\n", mypid);

        // Change priority
        setpriority(mypid, 1);
        printf("Child Process %d: Priority changed to 1\n", mypid);

        // Simulate work
        for (volatile int j = 0; j < 100000000; j++);
        
        exit(0);
    } else {
        wait(0); // Parent waits for the child
        printf("Test Priority Change Completed.\n");
    }

    exit(0);
}

