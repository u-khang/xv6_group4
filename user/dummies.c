#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void process_work(int priority) {
    setpriority(getpid(),priority);  // Set process priority
    int x=0;
    int z=0;
    while (1) {
        // Infinite loop doing nothing
        for(z = 0; z < 4000000000; z+=1)
	    x = x + 3.14*89.64;
    }
}

int main() {
    if (fork() == 0) {
        // First child process with priority 2
        process_work(2);
    }

    if (fork() == 0) {
        // Second child process with priority 3
        process_work(3);
    }

    // Parent process exits, leaving children running in background
    exit(0);
}
