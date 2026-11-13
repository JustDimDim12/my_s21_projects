#include <stdio.h>

int sum(int a, int b);
int rasn(int a, int b);
int proiz(int a, int b);
int del(int a, int b);

int main()
{   
    int a, b;
    int delet;
    char c;
    if (scanf("%d %d%c", &a, &b, &c) != 3 || c != '\n') {
        printf("n/a\n");
        return 0;
    }
    
    if (b != 0) {
        delet = a/b;
        printf("%d %d %d %d\n", sum(a,b), rasn(a,b), proiz(a,b), delet);
    }
    else {
        printf("%d %d %d n/a\n", sum(a,b), rasn(a,b), proiz(a,b));
    }

    return 0;
}

int sum(int a, int b){
    return a+b;
}

int rasn(int a, int b) {
    return a-b;
}

int proiz(int a, int b) {
    return a*b;
}

int del(int a, int b) {
    return a/b;
}