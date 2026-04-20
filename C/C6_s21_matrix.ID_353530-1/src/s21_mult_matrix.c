#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  s21_nullize(result);
  if (s21_matrix_alive(*A) == 0 && s21_matrix_alive(*B) == 0) {
    if (A->columns == B->rows) {
      res = s21_create_matrix(A->rows, B->columns, result);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            double element = 0;
            for (int n = 0; n < A->columns; n++) {
              element += A->matrix[i][n] * B->matrix[n][j];
            }
            result->matrix[i][j] = element;
          }
        }
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}