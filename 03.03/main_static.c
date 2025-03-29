#include <stdio.h>
#include "power_for.h"

int main() {
    int base = 2;
    int exponent = 10;
    int result = power_for(base, exponent);
    printf("2^10 using static library: %d\n", result);
    return 0;
}