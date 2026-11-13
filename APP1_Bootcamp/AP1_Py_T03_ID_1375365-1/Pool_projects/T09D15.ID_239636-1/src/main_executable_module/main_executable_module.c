#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#if USE_IO_MACRO
#include "../data_libs/data_io_macro.h"
#define input input_double
#define output output_double
#else
#include "../data_libs/data_io.h"
#endif

#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"
#include "sorting.h"

int main() {
    double *data;
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("ERROR");
        return 0;
    }
    data = (double *)malloc(n * sizeof(double));

    printf("LOAD DATA...\n");
    input(data, n);

    if (data[0] == NAN) {
        printf("ERROR");
        free(data);
        return 0;
    }

    printf("RAW DATA:\n\t");
    output(data, n);

    printf("\nNORMALIZED DATA:\n\t");
    normalization(data, n);
    output(data, n);

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    output(data, n);

    printf("\nFINAL DECISION:\n\t");
    if (make_decision(data, n))
        printf("YES");
    else
        printf("NO");
    free(data);
    return 0;
}