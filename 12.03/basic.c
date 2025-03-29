#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t result = fork();
    if (result == -1) {
        fprintf(stderr, "Fork error");
        return 1;
    }

    if (result == 0) {
        execl("./hw", "hw", NULL);
        fprintf(stderr, "Exec error");
        return 1;
    }else {
        printf("Основная программа тутааа!!!\n");
    }
    return 0;
}