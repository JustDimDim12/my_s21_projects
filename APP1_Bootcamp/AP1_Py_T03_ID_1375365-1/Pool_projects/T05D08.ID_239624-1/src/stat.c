#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        printf("n/a");
        return 0;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

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

int max(int *a, int n) {
    int max = a[0];
    for (int p = 1; p < n; p++) {
        if (a[p] > max) {
            max = a[p];
        }
    }
    return max;
}

int min(int *a, int n) {
    int min = a[0];
    for (int p = 1; p < n; p++) {
        if (a[p] < min) {
            min = a[p];
        }
    }
    return min;
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

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}