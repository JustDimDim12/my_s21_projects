#include <math.h>
#include <stdio.h>

double anyezy(double x) { return (powf(1, 3)) / (powf(1, 2) + powf(x, 2)); }

double bernully(double x) {
    return powf((powf(powf(1, 4) + 4 * powf(x, 2) * powf(1, 2), 0.5) - powf(x, 2) - powf(1, 2)), 0.5);
}

double gip(double x) { return powf(x, -2); }

int main() {
    double pi = 3.1415927;
    double dif = 2 * pi / 41;
    for (int i = 0; i < 42; i++) {
        double x = -pi + dif * i;
        if ((powf(powf(1, 4) + 4 * powf(x, 2) * powf(1, 2), 0.5) - powf(x, 2) - powf(1, 2)) >= 0) {
            printf("%.7lf | %.7lf | %.7lf | %.7lf\n", x, anyezy(x), bernully(x), gip(x));
        } else {
            printf("%.7lf | %.7lf | - | %.7lf\n", x, anyezy(x), gip(x));
        }
    }
    return 0;
}