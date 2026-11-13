#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  double det = 0;

  if (result != NULL) {
    s21_nullize(result);
  }
  if (A == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (s21_matrix_alive(*A) != OK) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALC_ERROR;
  } else {
    res = s21_determinant(A, &det);
    if (res == OK) {
      double threshold = 1e-6;
      if (A->rows > 2) {
        double max_elem = 0;
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            if (fabs(A->matrix[i][j]) > max_elem) {
              max_elem = fabs(A->matrix[i][j]);
            }
          }
        }
        threshold = 1e-6 * (max_elem > 1 ? max_elem : 1);
      }
      if (fabs(det) < threshold) {
        res = CALC_ERROR;
      }
    }
  }
  if (res == OK) {
    if (A->rows == 1) {
      res = s21_create_matrix(1, 1, result);
      if (res == OK) {
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      }
    } else {
      matrix_t calc_comp = {0};
      matrix_t transp = {0};
      res = s21_calc_complements(A, &calc_comp);

      if (res == OK) {
        res = s21_transpose(&calc_comp, &transp);
      }
      if (res == OK) {
        res = s21_create_matrix(A->rows, A->columns, result);
      }
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = transp.matrix[i][j] / det;
            if (fabs(result->matrix[i][j]) < 1e-15) {
              result->matrix[i][j] = 0.0;
            }
          }
        }
      }
      s21_remove_matrix(&calc_comp);
      s21_remove_matrix(&transp);
    }
  }

  if (res != OK && result != NULL) {
    s21_remove_matrix(result);
    s21_nullize(result);
  }

  return res;
}