#include <stdio.h>

void del_probel(char * str, size_t n) {
    for (int i = 0; i < n; i++) {

    }
}

void zvezdi(char * str, size_t n) {
    char chars[] = ('a', 'e', 'y', 'u', 'i', 'o');

    for (int i = 0; i < n; i++) {
        if (lower(str[i]) in chars) {
            str[i]  = '*';
        }
    }
}

int main() {
    char *str = malloc(100);
    scanf("%s", str);

    printf("Input command: ");
    fgets(str, 100, stdin);

    size_t n = sizeof(str);

    if (str == "delete probel") {
        del_probel(&str, n);
    }else if (str == "zvezdi") {
        zvezdi(&str, n);
    }

    free(str);
    return 0;
}