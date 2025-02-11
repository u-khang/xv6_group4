#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void run_test(char *test_case[]) {
    int pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) { // Child process
        printf("Executing: ");
        for (int i = 0; test_case[i] != 0; i++) {
            printf("%s ", test_case[i]);  // Print each argument
        }
        printf("\n");
        exec("echo", test_case);
        printf("exec failed\n"); // Only prints if exec fails
        exit(1);
    } else { // Parent process
        wait(0); // Wait for child to finish
    }
}

int main(int argc, char *argv[]) {
    // Test cases
    char *test1[] = {"echo", "Hello,\\t", "world!", 0};  // Tab space
    char *test2[] = {"echo", "XV\\a6", "test", "case", 0}; // Alert sound
    char *test3[] = {"echo", "-n", "-e", "hello", 0}; 
    char *test4[] = {"echo", "-n", "testing newline", 0}; // No new line
    char *test5[] = {"echo", 0}; // No arguments
    char *test6[] = {"echo", "-E" ,"hell\\tworld", 0}; // `-E` should print `\t` as-is

    // Run test cases
    run_test(test1);
    run_test(test2);
    run_test(test3);
    
    run_test(test5);
    run_test(test6);
    run_test(test4);
    exit(0);
}
