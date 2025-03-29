#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t result;
    char * ls_args[] = {
        "ls",
        "-l",
        NULL
    };
    result = fork();
    if (result == -1) {
        fprintf(stderr, "fork error\n");
        return 1;
    }

    /* Child */
    if (result == 0) {
        execvp("ls", ls_args);
        fprintf(stderr, "execve error\n");
        return 1;
    }
    
    /* Parent */
    return 0;
}