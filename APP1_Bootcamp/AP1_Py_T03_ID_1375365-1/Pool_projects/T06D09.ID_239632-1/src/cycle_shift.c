#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void shifting(int *a, int n, int shift);

int main() {
    int data[NMAX], n;
    if (input(data, &n)) {
        printf("n/a");
        return 0;
    }
    int c;
    if (scanf("%d", &c) != 1) {
        printf("n/a");
        return 0;
    }
    shifting(data, n, c);
    output(data, n);
    return 0;
}

int input(int *a, int *n) {
    int error = 0;
    if (scanf("%d", n) != 1) {
        error = 1;
    }
    if (*n <= 0 || *n > NMAX) {
        error = 1;
    }
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            error = 1;
        }
    }
    char c;
    if (scanf("%c", &c) != EOF && c != '\n') {
        error = 1;
    }
    return error;
}

void output(int *a, int n) {
    for (int p = 0; p < n; p++) {
        printf("%d", a[p]);
        if (p < n - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
}

void shifting(int *a, int n, int shift) {
    int b[NMAX];
    if (shift > 0) {
        while (shift > n) {
            shift -= n;
        }
        for (int i = 0; i < shift; i++) {
            b[i] = a[i];
        }
        for (int i = shift; i < n; i++) {
            a[i - shift] = a[i];
        }
        int count = 0;
        for (int i = n - shift; i < n; i++) {
            a[i] = b[count];
            count++;
        }
    } else if (shift < 0) {
        shift *= -1;
        while (shift > n) {
            shift -= n;
        }
        for (int i = 0; i < shift; i++) {
            b[shift - i - 1] = a[n - i - 1];
        }
        for (int i = n - 1; i > 0; i--) {
            a[i] = a[i - shift];
        }
        for (int i = 0; i < shift; i++) {
            a[i] = b[i];
        }
    }
}