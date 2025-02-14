#include "kernel/types.h"
#include "user/user.h"

// Helper function to run sleep and measure ticks
void run_sleep_test(int ticks) {
    printf("Test: sleep for %d ticks\n", ticks);

    int start_time = uptime();  // Get current ticks
    sleep(ticks);
    int end_time = uptime();  // Get ticks after sleep

    if ((end_time - start_time) >= ticks) {
        printf("Passed: Sleep for %d ticks was successful\n", ticks);
    } else {
        printf("Failed: Sleep for %d ticks did not work as expected\n", ticks);
    }
}

// Test cases
void test_sleep_50_ticks() { run_sleep_test(50); }
void test_sleep_80_ticks() { run_sleep_test(80); }
void test_sleep_150_ticks() { run_sleep_test(150); }


// Test invalid arguments (letters)
void test_invalid_argument_letters() {
    printf("Test: passing letters as argument\n");

    int pid = fork();
    if (pid == 0) {  // Child process
        char *argv[] = {"sleep", "abc", 0};  
        exec("sleep", argv);
        printf("Failed: sleep accepted non-numeric input!\n");
        exit(1);  
    } else {  // Parent process
        int status;
        wait(&status);
        if (status != 0) {
            printf("Passed: Invalid argument (letters) handled properly\n");
        } else {
            printf("Failed: sleep accepted non-numeric input!\n");
        }
    }
}

// Test multiple arguments
void test_multiple_arguments() {
    printf("Test: passing multiple arguments\n");

    int pid = fork();
    if (pid == 0) {  
        char *argv[] = {"sleep", "3", "4", 0};  // Multiple arguments
        exec("sleep", argv);
        printf("Failed: sleep accepted multiple arguments!\n");
        exit(1);  
    } else {  
        int status;
        wait(&status);
        if (status != 0) {
            printf("Passed: Multiple arguments detected and rejected\n");
        } else {
            printf("Failed: sleep accepted multiple arguments!\n");
        }
    }
}

// Test large argument
void test_large_argument() {
    printf("Test: passing large value\n");

    int pid = fork();
    if (pid == 0) {  
        char *argv[] = {"sleep", "10000000", 0};  
        exec("sleep", argv);
        printf("Failed: sleep accepted large value!\n");
        exit(1);  
    } else {  
        int status;
        wait(&status);
        if (status != 0) {
            printf("Passed: Large value handled properly\n");
        } else {
            printf("Failed: sleep accepted large value\n");
        }
    }
}



int main() {
    test_sleep_50_ticks();
    test_sleep_80_ticks();
    test_sleep_150_ticks();
    test_invalid_argument_letters();
    test_multiple_arguments();
    test_large_argument();
    exit(0);
}
