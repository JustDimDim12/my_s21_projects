#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  s21_nullize(result);
  if (A == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (s21_matrix_alive(*A) != OK) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALC_ERROR;
  } else {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      if (A->rows == 1) {
        result->matrix[0][0] = 1;
      } else {
        for (int i = 0; i < A->rows && res == OK; i++) {
          for (int j = 0; j < A->columns && res == OK; j++) {
            matrix_t minor = {0};
            double det = 0;

            res = s21_minor(A, i, j, &minor);
            if (res == OK) {
              res = s21_determinant(&minor, &det);
            }

            if (res == OK) {
              result->matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * det;
            }

            s21_remove_matrix(&minor);
          }
        }
      }

      if (res != OK) {
        s21_remove_matrix(result);
      }
    }
  }

  return res;
}