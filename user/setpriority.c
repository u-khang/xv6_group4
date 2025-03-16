#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: setpriority <priority>\n");
    exit(1);
  }

  int priority = atoi(argv[1]);
 
  int parentpid = getpid();
  printf("Process pid: %d\n", parentpid);
  int pid2=setpriority(2);
  printf("set priority %d to pid:%d\n", priority,pid2);
  

  exit(0);
}
