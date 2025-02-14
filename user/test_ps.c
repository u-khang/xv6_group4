#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

void
run_tests(void)
{
    printf("Running test cases for ps system call...\n");

    printf("Test Case 1: Verify ps Output for Basic Functionality\n");
    ps();

    printf("Test Case 2: Verify ps Output After Creating a New Process\n");
    int pid = fork();
    if(pid == 0) {
        // Child process
        printf("Child process created\n");
        exit(0);
    } else {
        // Parent process
        int status;
        ps();
        wait(&status);
        // ps();
    }

    printf("Test Case 3: Verify ps Output After Terminating a Process\n");
    pid = fork();
    if(pid == 0) {
        // Child process
        exit(0);
    } else {
        // Parent process
        sleep(50);
        int status;
        ps();
        wait(&status);
    }

    printf("All test cases completed.\n");
}

int
main(void)
{
    run_tests();
    exit(0);
}