#include <check.h>

#include "../../s21_matrix.h"

START_TEST(alive_normal_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(alive_1x1_matrix) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(alive_2x5_matrix) {
  matrix_t A;
  s21_create_matrix(2, 5, &A);

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(alive_5x2_matrix) {
  matrix_t A;
  s21_create_matrix(5, 2, &A);

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(alive_large_matrix) {
  matrix_t A;
  s21_create_matrix(100, 100, &A);

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(alive_rows_less_than_one) {
  matrix_t A;
  A.rows = 0;
  A.columns = 3;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_rows_negative) {
  matrix_t A;
  A.rows = -5;
  A.columns = 3;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_columns_less_than_one) {
  matrix_t A;
  A.rows = 3;
  A.columns = 0;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_columns_negative) {
  matrix_t A;
  A.rows = 3;
  A.columns = -2;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_both_less_than_one) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_both_negative) {
  matrix_t A;
  A.rows = -3;
  A.columns = -4;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_null_matrix_pointer) {
  matrix_t A;
  A.rows = 3;
  A.columns = 3;
  A.matrix = NULL;

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(alive_matrix_after_remove) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(alive_matrix_with_null_row) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  free(A.matrix[1]);
  A.matrix[1] = NULL;

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, OK);

  for (int i = 0; i < 3; i++) {
    if (i != 1) free(A.matrix[i]);
  }
  free(A.matrix);
}
END_TEST

START_TEST(alive_zero_initialized) {
  matrix_t A = {0};

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(alive_rows_valid_columns_invalid) {
  matrix_t A;
  A.rows = 3;
  A.columns = -1;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_columns_valid_rows_invalid) {
  matrix_t A;
  A.rows = -2;
  A.columns = 4;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_after_create_with_error) {
  matrix_t A;
  int create_code = s21_create_matrix(-1, 3, &A);
  ck_assert_int_eq(create_code, INCORRECT_MATRIX);

  int alive_code = s21_matrix_alive(A);
  ck_assert_int_eq(alive_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(alive_edge_case_1x0) {
  matrix_t A;
  A.rows = 1;
  A.columns = 0;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_edge_case_0x1) {
  matrix_t A;
  A.rows = 0;
  A.columns = 1;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  free(A.matrix);
}
END_TEST

START_TEST(alive_max_dimensions) {
  matrix_t A;
  A.rows = 1000000;
  A.columns = 1000000;
  A.matrix = (double **)malloc(sizeof(double *));

  int code = s21_matrix_alive(A);
  ck_assert_int_eq(code, OK);

  free(A.matrix);
}
END_TEST

Suite *matrix_alive_suite(void) {
  Suite *s = suite_create("MATRIX_ALIVE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, alive_normal_matrix);
  tcase_add_test(tc, alive_1x1_matrix);
  tcase_add_test(tc, alive_2x5_matrix);
  tcase_add_test(tc, alive_5x2_matrix);
  tcase_add_test(tc, alive_large_matrix);
  tcase_add_test(tc, alive_rows_less_than_one);
  tcase_add_test(tc, alive_rows_negative);
  tcase_add_test(tc, alive_columns_less_than_one);
  tcase_add_test(tc, alive_columns_negative);
  tcase_add_test(tc, alive_both_less_than_one);
  tcase_add_test(tc, alive_both_negative);
  tcase_add_test(tc, alive_null_matrix_pointer);
  tcase_add_test(tc, alive_matrix_after_remove);
  tcase_add_test(tc, alive_matrix_with_null_row);
  tcase_add_test(tc, alive_zero_initialized);
  tcase_add_test(tc, alive_rows_valid_columns_invalid);
  tcase_add_test(tc, alive_columns_valid_rows_invalid);
  tcase_add_test(tc, alive_after_create_with_error);
  tcase_add_test(tc, alive_edge_case_1x0);
  tcase_add_test(tc, alive_edge_case_0x1);
  tcase_add_test(tc, alive_max_dimensions);

  suite_add_tcase(s, tc);
  return s;
}