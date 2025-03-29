#include <stdio.h>

void to_lower(char *str) {
    while (*str != '\0') {
        if (*str >= 'A' && *str <= 'Z') {
            *str = *str - 'A' + 'a';
        }
        str++;
    }
}

int main() {
    char str[100];
    scanf("%s", str);
    to_lower(str);
    printf("%s\n", str);
    return 0;
}