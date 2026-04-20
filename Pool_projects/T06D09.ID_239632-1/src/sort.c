#include <stdio.h>
#define NMAX 10

int input(int *a, int n);
void output(int *a, int n);
void sort(int *a, int n);

int main() {
    int data[NMAX];
    if (input(data, NMAX)) {
        printf("n/a");
        return 0;
    }
    sort(data, NMAX);
    output(data, NMAX);
    return 0;
}

int input(int *a, int n) {
    //   if (scanf("%d", n) != 1) {
    //     return 1;
    //   }
    //   if (*n <= 0 || *n > NMAX) {
    //     return 1;
    //   }
    int error = 0;
    for (int *p = a; p - a < n; p++) {
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

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}