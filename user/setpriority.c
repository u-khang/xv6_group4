#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUM_PROCS 5

int main(int argc, char *argv[]) {
    if (argc !=3) {
        printf("usage setpriority pid priority\n");
        exit(0);
    }
    int pid = atoi(argv[1]);
    int priority = atoi(argv[2]);

    int status = setpriority(pid,priority);

    if (status==1){
        printf("error setting priority\n");
        exit(1);
    }
    exit(0);

    
    
}
