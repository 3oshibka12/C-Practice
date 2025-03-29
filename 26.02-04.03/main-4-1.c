#include <stdio.h>

void to_upper(char *str) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 'a' + 'A';
        }
        str++;
    }
}

void to_lower(char *str) {
    while (*str != '\0') {
        if (*str >= 'A' && *str <= 'Z') {
            *str = *str - 'A' + 'a';
        }
        str++;
    }
}

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

typedef struct {
    char *name;
    void (*func)(char*);
} Command;

int main() {
    Command commands[] = {
        {"upper", to_upper},
        {"lower", to_lower},
        {"reverse", reverse},
        {NULL, NULL}    // Завершающий элемент массива (чтоб цикл остановился)
    };

    char str[100], command[20];
    scanf("%s", str);

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "upper") == 0) {
            commands[0].func(str);
        }else if (strcmp(command, "lower") == 0) {
            commands[1].func(str);
        }else if (strcmp(command, "reverse") == 0) {
            commands[2].func(str);
        }else if (strcmp(command, "exit") == 0) {
            break;
        }else {
            printf("Unknown command\n");
            continue;
        }
        printf("%s\n", str);
    }
    return 0;
}