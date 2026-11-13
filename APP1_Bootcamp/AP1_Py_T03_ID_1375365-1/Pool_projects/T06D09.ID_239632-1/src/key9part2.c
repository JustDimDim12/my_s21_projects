#include <stdio.h>
#define LEN 100

int input(int *a, int *n);
void output(int *a, int n);
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int compare(int *buff1, int len1, int *buff2, int len2);

int main() {
    int data1[LEN] = {0}, data2[LEN] = {0};
    int n1 = 0, n2 = 0;

    if (input(data1, &n1) || n1 == 0) {
        printf("n/a");
        return 0;
    }
    if (input(data2, &n2) || n2 == 0) {
        printf("n/a");
        return 0;
    }

    int sum_data[LEN] = {0}, sum_length = 0;
    sum(data1, n1, data2, n2, sum_data, &sum_length);
    output(sum_data, sum_length);

    int sub_data[LEN] = {0}, sub_length = 0;
    sub(data1, n1, data2, n2, sub_data, &sub_length);
    if (sub_length == 0) {
        printf("n/a");
    } else {
        output(sub_data, sub_length);
    }

    return 0;
}

int input(int *a, int *n) {
    int error = 0;
    char c;
    *n = 0;
    while (*n < LEN) {
        if (scanf("%d%c", &a[*n], &c) != 2) {
            error = 1;
        }
        if (a[*n] < 0 || a[*n] > 9) {
            error = 1;
        }
        (*n)++;
        if (c == '\n') {
            break;
        }
    }
    if (*n == LEN && c != '\n') {
        while (getchar() != '\n');
        error = 1;
    }
    return error;
}

void output(int *a, int n) {
    if (n == 0) return;
    int is_zero = 1;
    for (int i = 0; i < n; i++) {
        if (!(a[i] == 0 && is_zero)) {
            printf("%d", a[i]);
            if (i < n - 1) {
                printf(" ");
            }
            is_zero = 0;
        }
    }
    printf("\n");
}

int compare(int *buff1, int len1, int *buff2, int len2) {
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    for (int i = 0; i < len1; i++) {
        if (buff1[i] > buff2[i]) return 1;
        if (buff1[i] < buff2[i]) return -1;
    }
    return 0;
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int carry = 0;
    int max_len = len1 > len2 ? len1 : len2;
    *result_length = max_len;

    for (int i = 0; i < max_len; i++) {
        int digit1 = i < len1 ? buff1[len1 - 1 - i] : 0;
        int digit2 = i < len2 ? buff2[len2 - 1 - i] : 0;

        int sum = digit1 + digit2 + carry;
        result[max_len - 1 - i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0) {
        for (int i = max_len; i > 0; i--) {
            result[i] = result[i - 1];
        }
        result[0] = carry;
        (*result_length)++;
    }
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    if (compare(buff1, len1, buff2, len2) < 0) {
        *result_length = 0;
        return;
    }

    int borrow = 0;
    *result_length = len1;

    for (int i = 0; i < len1; i++) {
        int digit1 = buff1[len1 - 1 - i];
        int digit2 = i < len2 ? buff2[len2 - 1 - i] : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[len1 - 1 - i] = diff;
    }

    while (*result_length > 1 && result[0] == 0) {
        for (int i = 0; i < *result_length - 1; i++) {
            result[i] = result[i + 1];
        }
        (*result_length)--;
    }

    if (*result_length == 0) {
        result[0] = 0;
        *result_length = 1;
    }
}