#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

// Function to format the file name
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void 
print_long_format(char *path, struct stat *st) {
    char *name = fmtname(path);
    int size = st->size;

    printf("%d %s\n", size, name);
}

// Recursive function to list directories
void
ls_recursive(char *path, int long_format, int show_hidden) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if(st.type == T_DIR) {
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      close(fd);
      return;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      if (show_hidden || de.name[0] != '.') {
        if (long_format) {
          print_long_format(buf, &st);
        } else {
          printf("%s\n", fmtname(buf));
        }
      }
      if (st.type == T_DIR && strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0) {
        ls_recursive(buf, long_format, show_hidden);
      }
    }
  } else {
    if (long_format) {
      print_long_format(path, &st);
    } else {
      printf("%s\n", fmtname(path));
    }
  }
  close(fd);
}

void ls(char *path, int long_format, int show_hidden, int recursive)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, O_RDONLY)) < 0) {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if (st.type == T_DIR) {
    if (recursive) {
      // Perform recursive listing if -R is specified
      ls_recursive(path, long_format, show_hidden);
    } else {
      // Non-recursive case: only list the directory contents
      if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
        printf("ls: path too long\n");
        close(fd);
        return;
      }
      strcpy(buf, path);
      p = buf + strlen(buf);
      *p++ = '/';

      while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0) continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
          printf("ls: cannot stat %s\n", buf);
          continue;
        }
        if (show_hidden || de.name[0] != '.') {
          if (long_format) {
            print_long_format(buf, &st);
          } else {
            printf("%s\n", fmtname(buf));
          }
        }
      }
    }
  } else {
    // If it's a file, just print it
    if (long_format) {
      print_long_format(path, &st);
    } else {
      printf("%s\n", fmtname(path));
    }
  }

  close(fd);
}


int
main(int argc, char *argv[])
{
  int i;
  int long_format = 0;
  int show_hidden = 0;
  int recursive = 0;

  // Parse command line options
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      char *p = argv[i] + 1;
      while (*p) {
        if (*p == 'l') long_format = 1;
        if (*p == 'a') show_hidden = 1;
        if (*p == 'R') recursive = 1;
        if (*p != 'l' && *p != 'a' && *p != 'R') {
          fprintf(2, "ls: invalid option\n");
          exit(1);
        }
       p++;
     }      
    }
  }

  // Determine the paths to list
  int path_start = 1;
  while (path_start < argc && argv[path_start][0] == '-') {
    path_start++;
  }

  if (path_start >= argc) {
    ls(".", long_format, show_hidden, recursive);
  } else {
    for (i = path_start; i < argc; i++) {
      ls(argv[i], long_format, show_hidden, recursive);
    }
  }
  exit(0);
}