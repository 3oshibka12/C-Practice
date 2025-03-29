int power_divide(int base, int exponent) {
    if (exponent == 0) return 1;
    if (exponent % 2 == 0) {
        int half = power_divide(base, exponent / 2);
        return half * half;
    } else {
        return base * power_divide(base, exponent - 1);
    }
}