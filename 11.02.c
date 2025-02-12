#include <stdio.h>

int task1() {
    float wei;
    scanf("%f", &wei);

    if (90.0 >= wei && wei >= 60.0) {
        printf("OK\n");
    } else {
        printf("NOT OK\n");
    }

    return 0;
}

int task2() {
    int s;
    scanf("%d", &s);

    if (s <= 500) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}

int task3() {
    char sim = getc(stdin);

    if ('A' <= sim && sim <= 'Z') {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}

int task4() {
    int s;
    scanf("%d", &s);

    if (s > 20250210) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}

int task5() {
    int s;
    scanf("%d", &s);

    if (s % 4 == 0) {
        printf("Yes: %d\n", s / 4);
    }else if (s % 3 == 0) {
        printf("Yes: %d\n", s / 3);
    }else if (s % 2 == 0) {
        printf("Yes: %d\n", s / 2);
    }else {
        printf("No\n");
    }

    return 0;
}

int task7() {
    float s;
    scanf("%f", &s);

    if (2.5 <= s && s <= 3.5) {
        printf("Ok\n");
    } else {
        printf("NOT OK\n");
    }
    
    return 0;
}

int task8() {
    int s;
    scanf("%d", &s);

    if (s % 4 == 0) {
        printf("Yes: %d\n", s / 4);
    }else {
        printf("No\n");
    }
    
    return 0;
}
int main() {
    task8();
    return 0;
}