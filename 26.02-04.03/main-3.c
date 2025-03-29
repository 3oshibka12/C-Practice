#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void task1() {
    int n;
    scanf("%d", &n);
    char ships[n][50];
    for (int i = 0; i < n; i++) {
        scanf("%49s", ships[i]);
    }
    int f = 0;
    for (int i = 0; i < n; i++) {
        if (!strncmp(ships[i], "SS", 2)) {
            f = 1;
            printf("%s\n", ships[i]);
            return 0;
        }
    }

    if (!f) {
        printf("Не найдено\n");
    }
}

void task2() {
    int n;
    scanf("%d", &n);
    char ans[n];
    char str[n];
    scanf("%s", str);
    // fgets(str, n, stdin);
    // str[strcspn(str, "\n")] = 0;

    char chars[] = "#*";

    size_t len = strspn(str, chars);

    strncpy(str, str + len, n - len);
    str[n - len] = 0;
    size_t pos = strcspn(str, chars);
    strncpy(str, str, pos);
    str[pos] = 0;
    printf("%d %s \n", strlen(str), str);


    // or


    char signal[101];
    printf("Input signal: ");
    scanf("%s", signal);

    size_t start = strspn(signal, "#*");

    size_t end = strlen(signal) - strcspn(signal + start, "#*");

    size_t length = end - start;

    char *message = strndup(signal + start, length);

    printf("Message: %s\n", message);
    printf("Length of message: %zu\n", length);

    free(message);
}

void task3() {
    char str[100];
    scanf("%s", str);
    int n = strlen(str);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            char *lname = strtok(str, ";");
            printf("%s\n", lname);
        }else {
            char *lname = strtok(NULL, ";");
            if (!lname) {
                break;
            }
            printf("%s\n", lname);
        }
    }
}

void task4() {
    char str[100];
    scanf("%s", str);
    
    if (strlen(str) == 11 && !strcasecmp(str, "launch-2025")) {
        printf("Код принят\n");
    } else {
        printf("Ошибка: неверный код!\n");
    }
}

void task5() {
    char str[200];
    scanf(" %199[^\n]", str);      // Не читаем пробельные символы вначале строки, а читаем все символы, кроме энтера, причем не более 199
    // str = *str2; - ерудна какая-то
    char *str2 = strdup(str);

    printf("Оригинал: %s \nКопия: %s\n", str, str2);

    free(str2);
}

int main() {
    task4();
    return 0;
}