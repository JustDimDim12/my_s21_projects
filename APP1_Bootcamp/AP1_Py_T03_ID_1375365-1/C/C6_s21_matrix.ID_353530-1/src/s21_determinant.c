#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;

  if (A == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (s21_matrix_alive(*A) != OK) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALC_ERROR;
  } else {
    *result = 0;

    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else {
      for (int i = 0; i < A->columns && res == OK; i++) {
        matrix_t minor = {0};
        double temp = 0;
        res = s21_minor(A, 0, i, &minor);

        if (res == OK) res = s21_determinant(&minor, &temp);
        if (res == OK) {
          *result += pow(-1, i) * A->matrix[0][i] * temp;
        }
        s21_remove_matrix(&minor);
      }
    }
  }

  if (res != OK && result != NULL) {
    *result = 0;
  }

  return res;
}