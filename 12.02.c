#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int age;
    float gpa;
};

struct Item {
    char name[50];
    int quantity;
    float price;
};


struct Event {
    char name[50];
    int day;
    int month;
    int year;
    char description[100];
};

struct Employee {
    char name[50];
    char position[50];
    float salary;
};

union Data {
    int i;
    float f;
    char str[50];
};

int task1() {
    int n;
    scanf("%d", &n);

    struct Student *students = malloc(sizeof(struct Student) * n);

    for (int i = 0; i < n; i++) {
        scanf("%s%d%f", students[i].name, &students[i].age, &students[i].gpa);
    }
    for (int i = 0; i < n; i++) {
        printf("Name: %s\nAge: %d\nGPA: %.2f\n\n", students[i].name, students[i].age, students[i].gpa);
    }
    
    return 0;
}

int task2() {
    int n;
    scanf("%d", &n);

    struct Item *items = malloc(sizeof(struct Item) * n);

    for (int i = 0; i < n; i++) {
        scanf("%s%d%f", items[i].name, &items[i].quantity, &items[i].price);
    }
    for (int i = 0; i < n; i++) {
        printf("Item: %s\nQuantity: %d\nPrice: %.2f\n\n", items[i].name, items[i].quantity, items[i].price);
    }
    
    return 0;
}

int task3() {
    int n;
    scanf("%d", &n);

    struct Event *events = malloc(sizeof(struct Event) * n);

    for (int i = 0; i < n; i++) {
        scanf("%s%d%d%d%s", events[i].name, &events[i].day, &events[i].month, &events[i].year, events[i].description);
    }
    for (int i = 0; i < n; i++) {
        printf("Event: %s\nDate: %d/%d/%d\nDescription: %s\n\n", events[i].name, events[i].day, events[i].month, events[i].year, events[i].description);
    }
    
    return 0;
}

int task4() {
    int n;
    scanf("%d", &n);

    struct Employee *employees = malloc(sizeof(struct Employee) * n);

    for (int i = 0; i < n; i++) {
        scanf("%s%s%f", employees[i].name, employees[i].position, &employees[i].salary);
    }
    for (int i = 0; i < n; i++) {
        printf("Name: %s\nPosition: %s\nSalary: %.2f\n\n", employees[i].name, employees[i].position, employees[i].salary);
    }
    
    return 0;
}

int task5() {
    int n;
    scanf("%d", &n);
    union Data data;
    if (n == 1) {
        scanf("%d", &data.i);
        printf("Integer: %d\n", data.i);
    } else if (n == 2) {
        scanf("%f", &data.f);
        printf("Float: %.2f\n", data.f);
    } else if (n == 3) {
        scanf("%s", data.str);
        printf("String: %s\n", data.str);
    }
    
    return 0;
}

int main() {
    task5();
    return 0;
}