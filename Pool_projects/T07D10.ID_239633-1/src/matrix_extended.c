#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void print_matrix(int **matrix, int rows, int cols);
void free_dynamic_matrix(int **matrix, int rows);

int main() {
    int choice;
    int n, m;

    if ((scanf("%d", &choice)) != 1 || choice < 1 || choice > 4) {
        printf("n/a");
        return 0;
    }

    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }

    if (choice == 1 && (n > MAX_SIZE || m > MAX_SIZE)) {
        printf("n/a");
        return 0;
    }

    int **matrix = NULL;

    switch (choice) {
        case 1: {
            static int static_matrix[MAX_SIZE][MAX_SIZE];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (scanf("%d", &static_matrix[i][j]) != 1) {
                        printf("n/a");
                        return 0;
                    }
                }
            }
            matrix = (int **)malloc(n * sizeof(int *));
            if (!matrix) {
                printf("n/a");
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
                    return 0;
                }
                for (int j = 0; j < m; j++) {
                    matrix[i][j] = static_matrix[i][j];
                }
            }
            break;
        }
        case 2: {
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
        case 3: {
            matrix = (int **)malloc(n * sizeof(int *));
            if (!matrix) {
                printf("n/a");
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
        case 4: {
            matrix = (int **)malloc(n * sizeof(int *) + n * m * sizeof(int));
            if (!matrix) {
                printf("n/a\n");
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

    print_matrix(matrix, n, m);
    int p_min_col = 0, p_max_row = 0;

    printf("\n");
    for (int i = 0; i < n; i++) {
        p_max_row = matrix[i][0];
        for (int j = 1; j < m; j++) {
            if (matrix[i][j] > p_max_row) {
                p_max_row = matrix[i][j];
            }
        }
        if (i != n - 1) {
            printf("%d ", p_max_row);
        } else {
            printf("%d", p_max_row);
        }
    }
    printf("\n");
    for (int j = 0; j < m; j++) {
        p_min_col = matrix[0][j];
        for (int i = 1; i < n; i++) {
            if (matrix[i][j] < p_min_col) {
                p_min_col = matrix[i][j];
            }
        }
        if (j != m - 1) {
            printf("%d ", p_min_col);
        } else {
            printf("%d", p_min_col);
        }
    }

    switch (choice) {
        case 1:
        case 2:
        case 3:
            free_dynamic_matrix(matrix, n);
            break;
        case 4:
            free(matrix);
            break;
    }

    return 0;
}

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) {
                printf(" ");
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}

void free_dynamic_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}