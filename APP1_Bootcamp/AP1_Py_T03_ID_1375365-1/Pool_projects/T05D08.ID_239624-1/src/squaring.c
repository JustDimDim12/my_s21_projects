#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        printf("n/a");
        return 0;
    }
    squaring(data, n);
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
        }
    }
}

void squaring(int *a, int n) {
    for (int p = 0; p < n; p++) {
        a[p] *= a[p];
    }
}