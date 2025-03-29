# Семинар 4 - Создание и использование статических и динамических библиотек

## **1. Создание Статической Библиотеки**

### **a. Реализация функции возведения в степень через цикл `for`**

1. **Создайте файл с кодом: `power_for.c`**

   ```c
   // power_for.c
   int power_for(int base, int exponent) {
       int result = 1;
       for (int i = 0; i < exponent; ++i) {
           result *= base;
       }
       return result;
   }
   ```

2. **Создайте заголовочный файл: `power_for.h`**

   ```c
   // power_for.h
   #ifndef POWER_FOR_H
   #define POWER_FOR_H

   int power_for(int base, int exponent);

   #endif // POWER_FOR_H
   ```

3. **Скомпилируйте в объектный файл и затем создайте статическую библиотеку**

   ```bash
   gcc -c power_for.c -o power_for.o
   ar rcs libpower_for.a power_for.o
   ```

## **2. Создание Динамической Библиотеки**

### **a. Реализация функции возведения в степень через деление основания на два (метод быстрого возведения в степень)**

1. **Создайте файл с кодом: `power_divide.c`**

   ```c
   // power_divide.c
   int power_divide(int base, int exponent) {
       if (exponent == 0) return 1;
       if (exponent % 2 == 0) {
           int half = power_divide(base, exponent / 2);
           return half * half;
       } else {
           return base * power_divide(base, exponent - 1);
       }
   }
   ```

2. **Создайте заголовочный файл: `power_divide.h`**

   ```c
   // power_divide.h
   #ifndef POWER_DIVIDE_H
   #define POWER_DIVIDE_H

   int power_divide(int base, int exponent);

   #endif // POWER_DIVIDE_H
   ```

3. **Скомпилируйте в динамическую библиотеку**

   ```bash
   gcc -fPIC -c power_divide.c -o power_divide.o
   gcc -shared -o libpower_divide.so power_divide.o
   ```

## **3. Реализация Программы, Использующей Статическую Библиотеку**

1. **Создайте файл с кодом: `main_static.c`**

   ```c
   // main_static.c
   #include <stdio.h>
   #include "power_for.h"

   int main() {
       int base = 2;
       int exponent = 10;
       int result = power_for(base, exponent);
       printf("2^10 using static library: %d\n", result);
       return 0;
   }
   ```

2. **Скомпилируйте и выполните программу с использованием статической библиотеки**

   ```bash
   gcc main_static.c -L. -lpower_for -o main_static
   ./main_static
   ```

## **4. Реализация Программы, Использующей Динамическую Библиотеку**

1. **Создайте файл с кодом: `main_dynamic.c`**

   ```c
   // main_dynamic.c
   #include <stdio.h>
   #include "power_divide.h"

   int main() {
       int base = 2;
       int exponent = 10;
       int result = power_divide(base, exponent);
       printf("2^10 using dynamic library: %d\n", result);
       return 0;
   }
   ```

2. **Скомпилируйте и выполните программу с использованием динамической библиотеки**

   ```bash
   gcc main_dynamic.c -L. -lpower_divide -o main_dynamic
   LD_LIBRARY_PATH=. ./main_dynamic
   ```

## **5. Объяснение и выводы**

- **Статическая библиотека**: Обратите внимание на то, как символы из статической библиотеки включаются в конечный исполняемый файл во время компиляции и связывания. Вы также можете рассмотреть размер итогового файла и загрузочное время.
  
- **Динамическая библиотека**: Обратите внимание на то, как динамическая библиотека загружается в память во время выполнения, и как это влияет на размер исполняемого файла. Также рассмотрите способы обновления динамических библиотек без необходимости перекомпиляции основной программы.

- **Сравнение алгоритмов**: Сравните два алгоритма по времени выполнения и эффективности использования ресурсов.
