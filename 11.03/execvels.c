#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

extern char ** environ;

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
        execve("/bin/ls", ls_args, environ);
        fprintf(stderr, "execve error\n");
        return 1;
    }
    
    /* Parent */
    return 0;
}