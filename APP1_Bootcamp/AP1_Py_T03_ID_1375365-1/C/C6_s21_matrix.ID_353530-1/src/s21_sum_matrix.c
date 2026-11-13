#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A == NULL || B == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (s21_matrix_alive(*A) != 0 || s21_matrix_alive(*B) != 0) {
    res = INCORRECT_MATRIX;
  } else if (A->rows == B->rows && A->columns == B->columns) {
    s21_nullize(result);
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    res = CALC_ERROR;
  }
  return res;
}