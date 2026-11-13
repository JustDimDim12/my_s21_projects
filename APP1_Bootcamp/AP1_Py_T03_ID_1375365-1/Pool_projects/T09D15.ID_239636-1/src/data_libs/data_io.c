#include "data_io.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void input(double *data, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &data[i]) != 1) {
            data[0] = NAN;
            return;
        }
    }
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf", data[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
}