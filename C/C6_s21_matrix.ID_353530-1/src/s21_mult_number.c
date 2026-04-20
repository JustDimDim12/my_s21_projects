#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (s21_matrix_alive(*A) == 0) {
    s21_nullize(result);
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}