#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define PATH_MAX 256

// Function to check if a directory exists
int directory_exists(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        if (st.type == T_DIR) {
            return 1;  // Directory exists
        } else {
            return -1; // Path exists but is NOT a directory
        }
    }
    return 0;  // Directory does not exist
}

// Function to create **parent directories one by one**
void create_recursive_directories(char *path) {
    char temp[PATH_MAX] = "";  // Start with an empty string
    char *p = path;
    int len = 0;  // Keep track of temp's length

    // If path starts with '/', manually add the first '/'
    if (*p == '/') {
        temp[len++] = '/';
        temp[len] = '\0';
        p++;  // Move past the first '/'
    }

    // Iterate over the given path, adding one character at a time
    for (; *p != '\0'; p++) {
        temp[len++] = *p;  // Append character to temp
        temp[len] = '\0';  // Null-terminate after each addition

        if (*p == '/') {  // When encountering '/', check directory
            int exists = directory_exists(temp);
            if (exists == -1) {
                fprintf(2, "mkdir: %s exists but is not a directory\n", temp);
                return;
            }
            if (exists == 0) {  // Directory does not exist, create it
                if (mkdir(temp) < 0) {
                    fprintf(2, "mkdir: failed to create %s\n", temp);
                    return;
                }
            }
        }
    }

    // Finally, create the full target directory if it doesn't exist
    int exists = directory_exists(temp);
    if (exists == -1) {
        fprintf(2, "mkdir: %s exists but is not a directory\n", temp);
    } else if (exists == 1) {
        fprintf(2, "mkdir: cannot create directory '%s': Directory already exists\n", temp);
    } else {
        if (mkdir(temp) < 0) {
            fprintf(2, "mkdir: failed to create %s\n", temp);
        }
    }
}

// Function to create a **single directory**
void create_single_directory(char *path) {
    int exists = directory_exists(path);
    if (exists == -1) {
        fprintf(2, "mkdir: %s exists but is not a directory\n", path);
    } else if (exists == 1) {
        fprintf(2, "mkdir: cannot create directory '%s': Directory already exists\n", path);
    } else {
        if (mkdir(path) < 0) {
            fprintf(2, "mkdir: %s failed to create\n", path);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Usage: mkdir [-p] directory...\n");
        exit(1);
    }

    // "-p" flag detection
    int recursive = (strcmp(argv[1], "-p") == 0);
    int startIndex = recursive ? 2 : 1;  // If "-p" is present, start at argv[2]

    for (int i = startIndex; i < argc; i++) {
        if (recursive) {
            create_recursive_directories(argv[i]);  // Calls recursive function
        } else {
            create_single_directory(argv[i]);  // Calls normal mkdir function
        }
    }

    exit(0);
}
