#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t result;
    result = fork();
    if (result == -1) {
        fprintf(stderr, "fork error\n");
        return 1;
    }

    /* Child */
    if (result == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        fprintf(stderr, "execve error\n");
        return 1;
    }
    
    /* Parent */
    return 0;
}