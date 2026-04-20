#include <stdio.h>
#include <stdlib.h>

int input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);
int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
int transpose(int **matrix, int n, int m);
int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);

int main() {
    int choice;

    if ((scanf("%d", &choice)) != 1 || choice < 1 || choice > 3) {
        printf("n/a\n");
        return 0;
    }

    int **matrix1 = NULL;

    switch (choice) {
        case 1: {
            int n1, m1;
            if (scanf("%d %d", &n1, &m1) != 2 || n1 <= 0 || m1 <= 0) {
                printf("n/a");
                return 0;
            }

            matrix1 = (int **)malloc(n1 * sizeof(int *) + n1 * m1 * sizeof(int));
            input(matrix1, &n1, &m1);

            int n2, m2;
            if (scanf("%d %d", &n2, &m2) != 2 || !(n2 == n1 && m2 == m1)) {
                printf("n/a");
                return 0;
            }

            int **matrix2 = NULL;
            matrix2 = (int **)malloc(n2 * sizeof(int *) + n2 * m2 * sizeof(int));
            input(matrix2, &n2, &m2);

            int n_sum = n1, m_sum = m1;
            int **sum_matrix = NULL;
            sum_matrix = (int **)malloc(n_sum * sizeof(int *) + n_sum * m_sum * sizeof(int));

            sum(matrix1, n1, m1, matrix2, n2, m2, sum_matrix, &n_sum, &m_sum);
            output(sum_matrix, n_sum, m_sum);
            free_dynamic_matrix(matrix1, n1);
            free_dynamic_matrix(matrix2, n2);
            free_dynamic_matrix(sum_matrix, n_sum);
            break;
        }
        case 2: {
            int n1, m1;
            if (scanf("%d %d", &n1, &m1) != 2 || n1 <= 0 || m1 <= 0) {
                printf("n/a");
                return 0;
            }

            matrix1 = (int **)malloc(n1 * sizeof(int *) + n1 * m1 * sizeof(int));
            input(matrix1, &n1, &m1);

            int n2, m2;
            if (scanf("%d %d", &n2, &m2) != 2 || (n2 != m1)) {
                printf("n/a");
                return 0;
            }

            int **matrix2 = NULL;
            matrix2 = (int **)malloc(n2 * sizeof(int *) + n2 * m2 * sizeof(int));
            input(matrix2, &n2, &m2);

            int n_mul = n1, m_mul = m2;
            int **mul_matrix = NULL;
            mul_matrix = (int **)malloc(n_mul * sizeof(int *) + n_mul * m_mul * sizeof(int));

            mul(matrix1, n1, m1, matrix2, n2, m2, mul_matrix, &n_mul, &m_mul);
            output(mul_matrix, n_mul, m_mul);
            free_dynamic_matrix(matrix1, n1);
            free_dynamic_matrix(matrix2, n2);
            free_dynamic_matrix(mul_matrix, n_mul);
            break;
        }
        case 3: {
            int n1, m1;
            if (scanf("%d %d", &n1, &m1) != 2 || n1 <= 0 || m1 <= 0) {
                printf("n/a");
                return 0;
            }

            matrix1 = (int **)malloc(n1 * sizeof(int *) + n1 * m1 * sizeof(int));
            input(matrix1, &n1, &m1);
            transpose(matrix1, n1, m1);
            output(matrix1, m1, n1) free_dynamic_matrix(matrix1, m1);
            break;
        }
        default:
            printf("n/a");
            return 0;
    }
    return 0;
}

int input(int **matrix, int *n, int *m) {
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
}

void output(int **matrix, int n, int m) {
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

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    for (int i = 0; i < *n_result) {
        for (int j = 0; i < *m_result) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return 0;
}

int transpose(int **matrix, int n, int m) {
    int **t_matrix[n][m] = matrix;
    for (int i = 0; i < n; i++) {
        if (n == m) {
            for (int j = 0; j < m; j++) {
                matrix[j][i] = t_matrix[i][j];
            }
        } /*else if (n > m) {

        } else {

        }*/
    }
}

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    // int n_mul = n1, m_mul = m2;
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            int temp_sum = 0;
            for (int k = 0; k < n_second) {
                temp_sum += matrix_first[i][k] * matrix_second[k][j];
            }
            matrix_result[i][j] = temp_sum;
        }
    }
}

void free_dynamic_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}