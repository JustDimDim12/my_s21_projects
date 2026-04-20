#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

enum {
  OK = 0,
  INCORRECT_MATRIX = 1,
  CALC_ERROR = 2,
};

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns,
                      matrix_t *result);      // создание матрицы
void s21_remove_matrix(matrix_t *A);          // очистка матрицы
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // сравнение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // сумма матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  // вычитание матриц
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result);  // умножение матрицы на число
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result);  // умножение матриц
int s21_transpose(matrix_t *A, matrix_t *result);  // транспонирование матрицы
int s21_calc_complements(
    matrix_t *A, matrix_t *result);  // матрица алгебраических дополнений
int s21_determinant(matrix_t *A, double *result);  // определитель матрицы
int s21_inverse_matrix(matrix_t *A, matrix_t *result);  // обратная матрица

// вспомогательные функции
void s21_nullize(matrix_t *A);  // стирание матрицы
int s21_matrix_alive(matrix_t A);  // проверка на существование матрицы
int s21_minor(matrix_t *A, int row, int column,
              matrix_t *result);  // минор матрицы

#endif