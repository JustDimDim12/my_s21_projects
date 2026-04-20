#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL) {
    return;
  }

  if (A->matrix != NULL && A->rows > 0) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }

  A->rows = 0;
  A->columns = 0;
}