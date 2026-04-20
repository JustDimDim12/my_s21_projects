#include "s21_matrix.h"

void s21_nullize(matrix_t *A) {
  if (A == NULL) return;

  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_matrix_alive(matrix_t A) {
  int res = OK;
  if (A.rows < 1 || A.columns < 1 || A.matrix == NULL || !A.matrix)
    res = INCORRECT_MATRIX;
  return res;
}

int s21_minor(matrix_t *A, int row, int column, matrix_t *result) {
  int res = OK;

  if (result != NULL) {
    s21_nullize(result);
  }
  if (A == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else {
    if (s21_matrix_alive(*A) != OK) {
      res = INCORRECT_MATRIX;
    } else {
      int safe_row = row;
      int safe_col = column;
      if (safe_row < 0) safe_row = 0;
      if (safe_row >= A->rows) safe_row = A->rows - 1;
      if (safe_col < 0) safe_col = 0;
      if (safe_col >= A->columns) safe_col = A->columns - 1;

      res = s21_create_matrix(A->rows - 1, A->columns - 1, result);

      if (res == OK) {
        int m_row = 0;
        for (int i = 0; i < A->rows && res == OK; i++) {
          if (i == safe_row) continue;
          int m_col = 0;
          for (int j = 0; j < A->columns && res == OK; j++) {
            if (j == safe_col) continue;
            result->matrix[m_row][m_col] = A->matrix[i][j];
            m_col++;
          }
          m_row++;
        }
      }
    }
  }

  if (res != OK && result != NULL) {
    s21_remove_matrix(result);
    s21_nullize(result);
  }

  return res;
}