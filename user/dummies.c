#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void infinite_process(int priority) {
    setpriority(getpid(), priority);  // Set priority for the process
    printf("Child process %d started with priority %d\n", getpid(), priority);
    sleep(10); //let other procs get scheduled
    while (1) {  // Infinite loop
        printf("Working on proc %d with priority %d\n", getpid(), priority);
        //starves all other procs other than if there is a higher priority than 1
        
    }
}

int main() {
    setpriority(getpid(), 0);  // Set the parent process priority to 0

    for (int i = 4; i > 0; i--) {  // Create 4 processes with priorities 4, 3, 2, 1
        if (fork() == 0) {
            infinite_process(i);  // Child process runs infinite loop with its priority
        }
    }

    // Parent exits, leaving child processes running
    exit(0);
}
