#include <stdio.h>
#include <math.h>

double func(double x) {
    return 7 * pow(10, -3) * pow(x, 4) + ((22.8 * powf(x, 1.0/3) - pow(10, 3)) * x + 3) / (x * x / 2) - x * powf(10 + x, 2.0/x) - 1.01;
}

int main() {
    double x;
    
    if (scanf("%lf", &x) != 1) {
        printf("n/a\n");
        return 0;
    }
    
    if (x <= 0) {
        printf("n/a\n");
        return 0;
    }
    
    double res = round(func(x) * 10) / 10;
    
    if (isnan(res) || isinf(res)) {
        printf("n/a\n");
    } else {
        printf("%.1f\n", res);
    }
    
    return 0;
}

//#include <stdio.h>
//#include <math.h>

//double func(int x);

//int main () {
//    int x;
//    if (scanf("%d", &x) != 1) {
//        printf("n/a\n");
//        return 0;
//    }
//    if (x <= 0) {
//        printf("n/a\n");
//        return 0;
//    }
//
//    double res = round(func(x) * 10) / 10;
//    printf("%.1f\n", res);
//    return 0;
//}

//double func(int x) {
//    double term3 = pow(10 + x, 2.0 / x);
//    if (isinf(term3)) {
//        printf("Ошибка: переполнение при x=%d\n", x);
//        return NAN;  // Not a Number
//    }
//    return 7*exp(-3) * pow(x, 4) + ((22.8 * pow(x, 1.0/3) - exp(3)) * x + 3) / (x * x / 2) - x * pow(10+x, 2.0/x) - 1.01;
//}