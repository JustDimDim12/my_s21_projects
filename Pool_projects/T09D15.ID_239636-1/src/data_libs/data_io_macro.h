#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DECLARE_IO_FUNCTIONS(type, format)      \
    void input_##type(type *data, int n) {      \
        for (int i = 0; i < n; i++) {           \
            if (scanf(format, &data[i]) != 1) { \
                printf("ERROR");                \
                data[0] = NAN;                  \
                exit(1);                        \
            }                                   \
        }                                       \
    }                                           \
    void output_##type(type *data, int n) {     \
        for (int i = 0; i < n; i++) {           \
            printf(format, data[i]);            \
            if (i < n - 1) printf(" ");         \
        }                                       \
        printf("\n");                           \
    }

DECLARE_IO_FUNCTIONS(double, "%lf")

#endif