#include <stdio.h>
#define NMAX 10

void input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int data[10], n;
    int check;
    input(data, &n);
    if (n == 0) {
        return 0;
    }
    printf("%d\n", sum_numbers(data, n));
    int ch_data[10];
    find_numbers(data, n, sum_numbers(data, n), ch_data);
    int v = find_numbers(data, n, sum_numbers(data, n), ch_data);
    output(ch_data, v);
    return 0;
}

void input(int *buffer, int *length) {
    if (scanf("%d", length) != 1 || *length <= 0 || *length > NMAX) {
        printf("n/a");
        *length = 0;
        return;
    }

    for (int *p = buffer; p - buffer < *length; p++) {
        if (scanf("%d", p) != 1) {
            printf("n/a");
            *length = 0;
            return;
        }
    }

    char c;
    if (scanf("%c", &c) != EOF && c != '\n') {
        printf("n/a");
        *length = 0;
    }
}

void output(int *buffer, int length) {
    for (int p = 0; p < length; p++) {
        printf("%d", buffer[p]);
        if (p < length - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum = sum + buffer[i];
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[count] = buffer[i];
            count++;
        }
    }
    return count;
}