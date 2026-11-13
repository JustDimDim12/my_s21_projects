#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void print_matrix(int **matrix, int rows, int cols);
void free_dynamic_matrix(int **matrix, int rows);
void sort_matrix(int **matrix, int rows, int cols);

int main() {
    int choice;
    int n, m;

    if ((scanf("%d", &choice)) != 1 || choice < 1 || choice > 3) {
        printf("n/a");
        return 0;
    }

    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }

    int **matrix = NULL;

    switch (choice) {
        case 1: {
            int *single_ptr = (int *)malloc(n * m * sizeof(int));
            if (!single_ptr) {
                printf("n/a");
                return 0;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (scanf("%d", &single_ptr[i * m + j]) != 1) {
                        printf("n/a");
                        free(single_ptr);
                        return 0;
                    }
                }
            }
            matrix = (int **)malloc(n * sizeof(int *));
            if (!matrix) {
                printf("n/a");
                free(single_ptr);
                return 0;
            }
            for (int i = 0; i < n; i++) {
                matrix[i] = (int *)malloc(m * sizeof(int));
                if (!matrix[i]) {
                    printf("n/a");
                    for (int k = 0; k < i; k++) {
                        free(matrix[k]);
                    }
                    free(matrix);
                    free(single_ptr);
                    return 0;
                }
                for (int j = 0; j < m; j++) {
                    matrix[i][j] = single_ptr[i * n + j];
                }
            }
            free(single_ptr);
            break;
        }
        case 2: {
            matrix = (int **)malloc(n * sizeof(int *));
            if (!matrix) {
                printf("n/a");
                return 0;
            }
            for (int i = 0; i < n; i++) {
                matrix[i] = (int *)malloc(m * sizeof(int));
                if (!matrix[i]) {
                    printf("n/a\n");
                    for (int k = 0; k < i; k++) {
                        free(matrix[k]);
                    }
                    free(matrix);
                    return 0;
                }
                for (int j = 0; j < m; j++) {
                    if (scanf("%d", &matrix[i][j]) != 1) {
                        printf("n/a");
                        free_dynamic_matrix(matrix, i);
                        return 0;
                    }
                }
            }
            break;
        }
        case 3: {
            matrix = (int **)malloc(n * sizeof(int *) + n * m * sizeof(int));
            if (!matrix) {
                printf("n/a");
                return 0;
            }
            int *data = (int *)(matrix + n);
            for (int i = 0; i < n; i++) {
                matrix[i] = data + i * m;
                for (int j = 0; j < m; j++) {
                    if (scanf("%d", &matrix[i][j]) != 1) {
                        printf("n/a");
                        free(matrix);
                        return 0;
                    }
                }
            }
            break;
        }
        default:
            printf("n/a");
            return 0;
    }

    sort_matrix(matrix, n, m);

    switch (choice) {
        case 1:
        case 2:
            free_dynamic_matrix(matrix, n);
            break;
        case 3:
            free(matrix);
            break;
    }

    return 0;
}

void free_dynamic_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int sum_row(int *row, int m) {
    int res = 0;
    for (int i = 0; i < m; i++) {
        res += row[i];
    }
    return res;
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void sort_matrix(int **matrix, int rows, int cols) {
    int sums[rows];
    for (int i = 0; i < rows; i++) {
        sums[i] = sum_row(matrix[i], cols);
    }
    sort(sums, rows);
    for (int num_sum = 0; num_sum < rows; num_sum++) {
        for (int i = 0; i < rows; i++) {
            if (sum_row(matrix[i], cols) == sums[num_sum]) {
                for (int j = 0; j < cols; j++) {
                    printf("%d", matrix[i][j]);
                    if (j < cols - 1) {
                        printf(" ");
                    } else {
                        printf("\n");
                    }
                }
            }
        }
    }
}