#include <stdio.h>
#define NMAX 10

int input(int *a, int n);
void output(int *a, int n);
void fast_sort(int *a, int n);
void pyr_sort(int *a, int n);

int main() {
    int data[NMAX];
    if (input(data, NMAX)) {
        printf("n/a");
        return 0;
    }
    int b[NMAX];
    for (int i = 0; i < NMAX; i++) {
        b[i] = data[i];
    }
    fast_sort(data, NMAX);
    output(data, NMAX);
    pyr_sort(b, NMAX);
    output(b, NMAX);
    return 0;
}

int input(int *a, int n) {
    int error = 0;
    //   if (scanf("%d", n) != 1) {
    //     return 1;
    //   }
    //   if (*n <= 0 || *n > NMAX) {
    //     return 1;
    //   }
    for (int *p = a; p - a < n; p++) {
        if (scanf("%d", p) != 1) {
            error = 1;
        }
    }
    char c;
    if (scanf("%c", &c) != EOF && c != '\n') {
        error = 1;
    }
    return error;
}

void output(int *a, int n) {
    for (int p = 0; p < n; p++) {
        printf("%d", a[p]);
        if (p < n - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *a, int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return i + 1;
}

void quick_sort(int *a, int low, int high) {
    if (low < high) {
        int pivot_index = partition(a, low, high);
        quick_sort(a, low, pivot_index - 1);
        quick_sort(a, pivot_index + 1, high);
    }
}

void fast_sort(int *a, int n) { quick_sort(a, 0, n - 1); }

void heapify(int *a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) {
        largest = left;
    }

    if (right < n && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

void pyr_sort(int *a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}