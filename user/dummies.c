#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void infinite_process(int priority) {
    setpriority(getpid(), priority);  // Set priority for the process

    

    int x = 0;
    while (1) {  // Infinite loop
        x = x + 1;  // Dummy operation to keep CPU busy
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: set_infinite_process <priority>\n");
        exit(1);
    }

    int priority = atoi(argv[1]);  // Convert argument to integer

    if (fork() == 0) {
        // Child process runs infinite loop with given priority
        infinite_process(priority);
    }

    // Parent exits, leaving the child running
    exit(0);
}
