#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;

  if (result != NULL) {
    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;
  }

  if (rows < 1 || columns < 1 || result == NULL) {
    res = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)calloc(rows, sizeof(double *));
    int i;
    for (i = 0; i < rows && res == OK; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        res = INCORRECT_MATRIX;
      }
    }

    if (res != OK) {
      for (int j = 0; j < i; j++) {
        if (result->matrix[j] != NULL) {
          free(result->matrix[j]);
          result->matrix[j] = NULL;
        }
      }
      free(result->matrix);
      result->matrix = NULL;
      result->rows = 0;
      result->columns = 0;
    }
  }

  return res;
}