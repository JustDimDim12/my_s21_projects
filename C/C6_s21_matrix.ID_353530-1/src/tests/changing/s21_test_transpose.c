#include <check.h>

#include "../../s21_matrix.h"

START_TEST(transpose_3x2) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 3;
  expected.matrix[0][2] = 5;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 4;
  expected.matrix[1][2] = 6;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_2x3) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 5;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 6;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_3x3) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 7;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 6;
  expected.matrix[2][2] = 9;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_1x1) {
  matrix_t A, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 42;
  expected.matrix[0][0] = 42;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_1x4) {
  matrix_t A, result, expected;
  s21_create_matrix(1, 4, &A);
  s21_create_matrix(4, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;

  expected.matrix[0][0] = 1;
  expected.matrix[1][0] = 2;
  expected.matrix[2][0] = 3;
  expected.matrix[3][0] = 4;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_4x1) {
  matrix_t A, result, expected;
  s21_create_matrix(4, 1, &A);
  s21_create_matrix(1, 4, &expected);

  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[3][0] = 4;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix[0][3] = 4;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_float) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[1][0] = 3.5;
  A.matrix[1][1] = 4.5;

  expected.matrix[0][0] = 1.5;
  expected.matrix[0][1] = 3.5;
  expected.matrix[1][0] = 2.5;
  expected.matrix[1][1] = 4.5;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_negative) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &expected);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -6;

  expected.matrix[0][0] = -1;
  expected.matrix[0][1] = -4;
  expected.matrix[1][0] = -2;
  expected.matrix[1][1] = -5;
  expected.matrix[2][0] = -3;
  expected.matrix[2][1] = -6;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_zero) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 0;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_incorrect_matrix) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(transpose_null_matrix) {
  matrix_t result;

  int code = s21_transpose(NULL, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(transpose_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int code = s21_transpose(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_large) {
  matrix_t A, result, expected;
  s21_create_matrix(100, 100, &A);
  s21_create_matrix(100, 100, &expected);

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      A.matrix[i][j] = i * 100 + j;
      expected.matrix[j][i] = i * 100 + j;
    }
  }

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_double_transpose) {
  matrix_t A, result1, result2;
  s21_create_matrix(2, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  int code = s21_transpose(&A, &result1);
  ck_assert_int_eq(code, OK);

  code = s21_transpose(&result1, &result2);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result2, &A);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(transpose_identity) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 1;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &A);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_symmetric) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = 6;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &A);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_precision) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 0.12345678;
  A.matrix[0][1] = 0.87654321;
  A.matrix[1][0] = 0.23456789;
  A.matrix[1][1] = 0.76543210;

  expected.matrix[0][0] = 0.12345678;
  expected.matrix[0][1] = 0.23456789;
  expected.matrix[1][0] = 0.87654321;
  expected.matrix[1][1] = 0.76543210;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *transpose_suite(void) {
  Suite *s = suite_create("TRANSPOSE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, transpose_3x2);
  tcase_add_test(tc, transpose_2x3);
  tcase_add_test(tc, transpose_3x3);
  tcase_add_test(tc, transpose_1x1);
  tcase_add_test(tc, transpose_1x4);
  tcase_add_test(tc, transpose_4x1);
  tcase_add_test(tc, transpose_float);
  tcase_add_test(tc, transpose_negative);
  tcase_add_test(tc, transpose_zero);
  tcase_add_test(tc, transpose_incorrect_matrix);
  tcase_add_test(tc, transpose_null_matrix);
  tcase_add_test(tc, transpose_null_result);
  tcase_add_test(tc, transpose_large);
  tcase_add_test(tc, transpose_double_transpose);
  tcase_add_test(tc, transpose_identity);
  tcase_add_test(tc, transpose_symmetric);
  tcase_add_test(tc, transpose_precision);

  suite_add_tcase(s, tc);
  return s;
}