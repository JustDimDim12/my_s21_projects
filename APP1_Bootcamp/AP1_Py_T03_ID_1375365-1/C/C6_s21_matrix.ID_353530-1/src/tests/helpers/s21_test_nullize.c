#include <check.h>

#include "../../s21_matrix.h"

START_TEST(nullize_normal_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[2][2] = 3;

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(nullize_1x1_matrix) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 42;

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(nullize_2x5_matrix) {
  matrix_t A;
  s21_create_matrix(2, 5, &A);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = i * 5 + j;
    }
  }

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(nullize_5x2_matrix) {
  matrix_t A;
  s21_create_matrix(5, 2, &A);

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(nullize_large_matrix) {
  matrix_t A;
  s21_create_matrix(100, 100, &A);

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(nullize_already_null_matrix) {
  matrix_t A = {0};

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(nullize_after_remove) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(nullize_negative_dimensions) {
  matrix_t A;
  A.rows = -5;
  A.columns = -3;
  A.matrix = (double **)malloc(sizeof(double *));

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  free(A.matrix);
}
END_TEST

START_TEST(nullize_zero_dimensions) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = (double **)malloc(sizeof(double *));

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  free(A.matrix);
}
END_TEST

START_TEST(nullize_with_null_rows) {
  matrix_t A;
  A.rows = 3;
  A.columns = 3;
  A.matrix = NULL;

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(nullize_null_pointer) {
  matrix_t *A = NULL;

  s21_nullize(A);

  ck_assert_ptr_null(A);
}
END_TEST

START_TEST(nullize_twice) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  s21_nullize(&A);
  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(nullize_check_independence) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1;
  B.matrix[0][0] = 2;

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  ck_assert_ptr_nonnull(B.matrix);
  ck_assert_int_eq(B.rows, 3);
  ck_assert_int_eq(B.columns, 3);
  ck_assert_double_eq(B.matrix[0][0], 2);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(nullize_after_create_error) {
  matrix_t A;
  s21_create_matrix(-1, 3, &A);

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(nullize_struct_with_garbage) {
  matrix_t A;
  A.rows = 100;
  A.columns = 200;
  A.matrix = (double **)0xdeadbeef;

  s21_nullize(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(nullize_and_recreate) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  s21_nullize(&A);

  int code = s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(A.rows, 2);
  ck_assert_int_eq(A.columns, 2);
  ck_assert_ptr_nonnull(A.matrix);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(nullize_after_operations) {
  matrix_t A, B, C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  s21_sum_matrix(&A, &B, &C);

  s21_nullize(&C);

  ck_assert_ptr_null(C.matrix);
  ck_assert_int_eq(C.rows, 0);
  ck_assert_int_eq(C.columns, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(nullize_after_mult_number) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  s21_mult_number(&A, 2.0, &result);

  s21_nullize(&result);

  ck_assert_ptr_null(result.matrix);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(nullize_after_transpose) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  s21_transpose(&A, &result);

  s21_nullize(&result);

  ck_assert_ptr_null(result.matrix);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *nullize_suite(void) {
  Suite *s = suite_create("NULLIZE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, nullize_normal_matrix);
  tcase_add_test(tc, nullize_1x1_matrix);
  tcase_add_test(tc, nullize_2x5_matrix);
  tcase_add_test(tc, nullize_5x2_matrix);
  tcase_add_test(tc, nullize_large_matrix);
  tcase_add_test(tc, nullize_already_null_matrix);
  tcase_add_test(tc, nullize_after_remove);
  tcase_add_test(tc, nullize_negative_dimensions);
  tcase_add_test(tc, nullize_zero_dimensions);
  tcase_add_test(tc, nullize_with_null_rows);
  tcase_add_test(tc, nullize_null_pointer);
  tcase_add_test(tc, nullize_twice);
  tcase_add_test(tc, nullize_check_independence);
  tcase_add_test(tc, nullize_after_create_error);
  tcase_add_test(tc, nullize_struct_with_garbage);
  tcase_add_test(tc, nullize_and_recreate);
  tcase_add_test(tc, nullize_after_operations);
  tcase_add_test(tc, nullize_after_mult_number);
  tcase_add_test(tc, nullize_after_transpose);

  suite_add_tcase(s, tc);
  return s;
}