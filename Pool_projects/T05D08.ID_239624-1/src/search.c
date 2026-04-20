#include <math.h>
#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);

/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        printf("n/a");
        return 0;
    }
    int res = 0;
    double m = mean(data, n);
    double v = variance(data, n);
    double threshold = m + 3 * sqrt(v);
    for (int i = 0; i < n; i++) {
        if ((data[i] % 2 == 0) && (data[i] >= m) && (data[i] <= threshold) && (data[i] != 0)) {
            res = data[i];
            break;
        }
    }
    printf("%d", res);
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

double mean(int *a, int n) {
    double res;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    n = (double)n;
    res = sum / n;
    return res;
}

double variance(int *a, int n) {
    double res;
    int sqr[NMAX];
    for (int p = 0; p < n; p++) {
        sqr[p] = a[p] * a[p];
    }
    res = mean(sqr, n) - (mean(a, n) * mean(a, n));
    return res;
}