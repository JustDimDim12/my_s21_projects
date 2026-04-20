#include "data_stat.h"

double max(double *data, int n) {
    double max = data[0];
    for (int p = 1; p < n; p++) {
        if (data[p] > max) {
            max = data[p];
        }
    }
    return max;
}

double min(double *data, int n) {
    double min = data[0];
    for (int p = 1; p < n; p++) {
        if (data[p] < min) {
            min = data[p];
        }
    }
    return min;
}

double mean(double *data, int n) {
    double res;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    n = (double)n;
    res = sum / n;
    return res;
}

double variance(double *data, int n) {
    double res;
    double sqr[n];
    for (int p = 0; p < n; p++) {
        sqr[p] = data[p] * data[p];
    }
    res = mean(sqr, n) - (mean(data, n) * mean(data, n));
    return res;
}