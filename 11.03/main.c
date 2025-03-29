#include <stdlib.h>
#include <stdio.h>
// #include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    // system ("uname");

    // system ("sleep 5 &");
    // printf("end-of-program\n");

    // system("cd abracadabra");

    int uid = getuid();
    struct passwd * pwdp = getpwuid(uid);

    if (pwdp == NULL) {
        fprintf(stderr, "Bad username\n");
        return 1;
    }

    printf("PID:.%d\n", getuid());
    return 0;
}