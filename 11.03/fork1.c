#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    printf("Hello world\n");
    sleep(15);
    return 0;
}