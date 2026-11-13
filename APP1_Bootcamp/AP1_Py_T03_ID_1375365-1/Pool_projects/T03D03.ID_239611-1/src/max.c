#include <stdio.h>

int max(int a, int b);

int main()
{   
    int a, b;
    char c;
    if (scanf("%d %d%c", &a, &b, &c) != 3 || c != '\n') {
        printf("n/a\n");
        return 0;
    }
    printf("%d\n", max(a,b));
    return 0;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}