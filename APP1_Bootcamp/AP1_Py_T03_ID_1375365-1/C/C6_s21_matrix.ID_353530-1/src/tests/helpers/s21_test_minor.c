#include <check.h>

#include "../../s21_matrix.h"

START_TEST(minor_3x3_0_0) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 5;
  expected.matrix[0][1] = 6;
  expected.matrix[1][0] = 8;
  expected.matrix[1][1] = 9;

  int code = s21_minor(&A, 0, 0, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_0_1) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = 6;
  expected.matrix[1][0] = 7;
  expected.matrix[1][1] = 9;

  int code = s21_minor(&A, 0, 1, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_0_2) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = 5;
  expected.matrix[1][0] = 7;
  expected.matrix[1][1] = 8;

  int code = s21_minor(&A, 0, 2, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_1_0) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 8;
  expected.matrix[1][1] = 9;

  int code = s21_minor(&A, 1, 0, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_1_1) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

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
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 7;
  expected.matrix[1][1] = 9;

  int code = s21_minor(&A, 1, 1, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_1_2) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

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
  expected.matrix[0][1] = 2;
  expected.matrix[1][0] = 7;
  expected.matrix[1][1] = 8;

  int code = s21_minor(&A, 1, 2, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_2_0) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 5;
  expected.matrix[1][1] = 6;

  int code = s21_minor(&A, 2, 0, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_2_1) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

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
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 6;

  int code = s21_minor(&A, 2, 1, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_3x3_2_2) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

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
  expected.matrix[0][1] = 2;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 5;

  int code = s21_minor(&A, 2, 2, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_4x4_1_2) {
  matrix_t A, result, expected;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(3, 3, &expected);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i * 4 + j + 1;
    }
  }

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 4;
  expected.matrix[1][0] = 9;
  expected.matrix[1][1] = 10;
  expected.matrix[1][2] = 12;
  expected.matrix[2][0] = 13;
  expected.matrix[2][1] = 14;
  expected.matrix[2][2] = 16;

  int code = s21_minor(&A, 1, 2, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_2x2_0_0) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  expected.matrix[0][0] = 4;

  int code = s21_minor(&A, 0, 0, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_2x2_0_1) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  expected.matrix[0][0] = 3;

  int code = s21_minor(&A, 0, 1, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_2x2_1_0) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  expected.matrix[0][0] = 2;

  int code = s21_minor(&A, 1, 0, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_2x2_1_1) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  expected.matrix[0][0] = 1;

  int code = s21_minor(&A, 1, 1, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_float_values) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[0][2] = 3.5;
  A.matrix[1][0] = 4.5;
  A.matrix[1][1] = 5.5;
  A.matrix[1][2] = 6.5;
  A.matrix[2][0] = 7.5;
  A.matrix[2][1] = 8.5;
  A.matrix[2][2] = 9.5;

  expected.matrix[0][0] = 5.5;
  expected.matrix[0][1] = 6.5;
  expected.matrix[1][0] = 8.5;
  expected.matrix[1][1] = 9.5;

  int code = s21_minor(&A, 0, 0, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_negative_values) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = -8;
  A.matrix[2][2] = -9;

  expected.matrix[0][0] = -5;
  expected.matrix[0][1] = -6;
  expected.matrix[1][0] = -8;
  expected.matrix[1][1] = -9;

  int code = s21_minor(&A, 0, 0, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(minor_incorrect_matrix) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  int code = s21_minor(&A, 0, 0, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(minor_null_matrix) {
  matrix_t result;

  int code = s21_minor(NULL, 0, 0, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(minor_null_result) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  int code = s21_minor(&A, 0, 0, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(minor_row_out_of_range) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  int code = s21_minor(&A, 3, 0, &result);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(minor_column_out_of_range) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  int code = s21_minor(&A, 0, 3, &result);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(minor_both_out_of_range) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  int code = s21_minor(&A, 5, 5, &result);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(minor_negative_row) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  int code = s21_minor(&A, -1, 0, &result);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(minor_negative_column) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  int code = s21_minor(&A, 0, -2, &result);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *minor_suite(void) {
  Suite *s = suite_create("MINOR");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, minor_3x3_0_0);
  tcase_add_test(tc, minor_3x3_0_1);
  tcase_add_test(tc, minor_3x3_0_2);
  tcase_add_test(tc, minor_3x3_1_0);
  tcase_add_test(tc, minor_3x3_1_1);
  tcase_add_test(tc, minor_3x3_1_2);
  tcase_add_test(tc, minor_3x3_2_0);
  tcase_add_test(tc, minor_3x3_2_1);
  tcase_add_test(tc, minor_3x3_2_2);
  tcase_add_test(tc, minor_4x4_1_2);
  tcase_add_test(tc, minor_2x2_0_0);
  tcase_add_test(tc, minor_2x2_0_1);
  tcase_add_test(tc, minor_2x2_1_0);
  tcase_add_test(tc, minor_2x2_1_1);
  tcase_add_test(tc, minor_float_values);
  tcase_add_test(tc, minor_negative_values);
  tcase_add_test(tc, minor_incorrect_matrix);
  tcase_add_test(tc, minor_null_matrix);
  tcase_add_test(tc, minor_null_result);
  tcase_add_test(tc, minor_row_out_of_range);
  tcase_add_test(tc, minor_column_out_of_range);
  tcase_add_test(tc, minor_both_out_of_range);
  tcase_add_test(tc, minor_negative_row);
  tcase_add_test(tc, minor_negative_column);

  suite_add_tcase(s, tc);
  return s;
}