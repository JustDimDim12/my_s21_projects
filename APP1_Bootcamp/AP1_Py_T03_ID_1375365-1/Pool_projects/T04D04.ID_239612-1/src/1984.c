#include <stdio.h>

int is_del(int c, int b) {
    int a;
    if (c < 0) {
        a = c * (-1);
    } else {
        a = c;
    }
    while (a >= b) {
        a -= b;
    }
    if (a == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_prime(int b) {
    int a;
    if (b < 0) {
        a = b * (-1);
    } else {
        a = b;
    }

    if (a <= 1) return 0;

    if (a <= 3) return 1;

    if ((a & 1) == 0) return 0;

    for (int i = 3; i * i <= a; i += 2) {
        int temp = 0;
        while (temp < a) temp += i;
        if (temp == a) return 0;
    }
    return 1;
}

int npd(int c) {
    int a;
    if (c < 0) {
        a = c * (-1);
    } else {
        a = c;
    }
    for (int i = a - 1; i > 1; i--) {
        if (is_del(a, i) && is_prime(i)) {
            return i;
        }
    }
    return a;
}

int main() {
    int a;
    if (scanf("%d", &a) != 1) {
        printf("n/a\n");
        return 0;
    }

    printf("%d\n", npd(a));
    return 0;
}