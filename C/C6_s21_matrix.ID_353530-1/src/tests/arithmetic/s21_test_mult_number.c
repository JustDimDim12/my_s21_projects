#include <check.h>

#include "../../s21_matrix.h"

START_TEST(mult_number_3x3_positive) {
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

  double number = 2.0;

  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 6;
  expected.matrix[1][0] = 8;
  expected.matrix[1][1] = 10;
  expected.matrix[1][2] = 12;
  expected.matrix[2][0] = 14;
  expected.matrix[2][1] = 16;
  expected.matrix[2][2] = 18;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_3x3_negative) {
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

  double number = -3.0;

  expected.matrix[0][0] = -3;
  expected.matrix[0][1] = -6;
  expected.matrix[0][2] = -9;
  expected.matrix[1][0] = -12;
  expected.matrix[1][1] = -15;
  expected.matrix[1][2] = -18;
  expected.matrix[2][0] = -21;
  expected.matrix[2][1] = -24;
  expected.matrix[2][2] = -27;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_3x3_zero) {
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

  double number = 0.0;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 0;
  expected.matrix[1][2] = 0;
  expected.matrix[2][0] = 0;
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = 0;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_3x3_float) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[0][2] = 3.5;
  A.matrix[1][0] = 4.5;
  A.matrix[1][1] = 5.5;
  A.matrix[1][2] = 6.5;
  A.matrix[2][0] = 7.5;
  A.matrix[2][1] = 8.5;
  A.matrix[2][2] = 9.5;

  double number = 2.5;

  expected.matrix[0][0] = 3.75;
  expected.matrix[0][1] = 6.25;
  expected.matrix[0][2] = 8.75;
  expected.matrix[1][0] = 11.25;
  expected.matrix[1][1] = 13.75;
  expected.matrix[1][2] = 16.25;
  expected.matrix[2][0] = 18.75;
  expected.matrix[2][1] = 21.25;
  expected.matrix[2][2] = 23.75;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_2x4_positive) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(2, 4, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 6;
  A.matrix[1][2] = 7;
  A.matrix[1][3] = 8;

  double number = 3.0;

  expected.matrix[0][0] = 3;
  expected.matrix[0][1] = 6;
  expected.matrix[0][2] = 9;
  expected.matrix[0][3] = 12;
  expected.matrix[1][0] = 15;
  expected.matrix[1][1] = 18;
  expected.matrix[1][2] = 21;
  expected.matrix[1][3] = 24;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_1x1) {
  matrix_t A, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 5;

  double number = 7.0;
  expected.matrix[0][0] = 35;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_4x1) {
  matrix_t A, result, expected;
  s21_create_matrix(4, 1, &A);
  s21_create_matrix(4, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[3][0] = 4;

  double number = 2.0;

  expected.matrix[0][0] = 2;
  expected.matrix[1][0] = 4;
  expected.matrix[2][0] = 6;
  expected.matrix[3][0] = 8;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_1x4) {
  matrix_t A, result, expected;
  s21_create_matrix(1, 4, &A);
  s21_create_matrix(1, 4, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;

  double number = 2.0;

  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 6;
  expected.matrix[0][3] = 8;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_incorrect_matrix) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  double number = 5.0;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(mult_number_null_matrix) {
  matrix_t result;

  double number = 5.0;

  int code = s21_mult_number(NULL, number, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(mult_number_null_result) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  double number = 5.0;

  int code = s21_mult_number(&A, number, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_large_values) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1000;
  A.matrix[0][1] = 2000;
  A.matrix[1][0] = 3000;
  A.matrix[1][1] = 4000;

  double number = 1000.0;

  expected.matrix[0][0] = 1000000;
  expected.matrix[0][1] = 2000000;
  expected.matrix[1][0] = 3000000;
  expected.matrix[1][1] = 4000000;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_small_values) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 0.001;
  A.matrix[0][1] = 0.002;
  A.matrix[1][0] = 0.003;
  A.matrix[1][1] = 0.004;

  double number = 0.001;

  expected.matrix[0][0] = 0.000001;
  expected.matrix[0][1] = 0.000002;
  expected.matrix[1][0] = 0.000003;
  expected.matrix[1][1] = 0.000004;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_negative_float) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = -2.5;
  A.matrix[1][0] = -3.5;
  A.matrix[1][1] = 4.5;

  double number = -2.0;

  expected.matrix[0][0] = -3.0;
  expected.matrix[0][1] = 5.0;
  expected.matrix[1][0] = 7.0;
  expected.matrix[1][1] = -9.0;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_check_precision) {
  matrix_t A, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 0.12345678;

  double number = 2.0;
  expected.matrix[0][0] = 0.24691356;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *mult_number_suite(void) {
  Suite *s = suite_create("MULT_NUMBER");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, mult_number_3x3_positive);
  tcase_add_test(tc, mult_number_3x3_negative);
  tcase_add_test(tc, mult_number_3x3_zero);
  tcase_add_test(tc, mult_number_3x3_float);
  tcase_add_test(tc, mult_number_2x4_positive);
  tcase_add_test(tc, mult_number_1x1);
  tcase_add_test(tc, mult_number_4x1);
  tcase_add_test(tc, mult_number_1x4);
  tcase_add_test(tc, mult_number_incorrect_matrix);
  tcase_add_test(tc, mult_number_null_matrix);
  tcase_add_test(tc, mult_number_null_result);
  tcase_add_test(tc, mult_number_large_values);
  tcase_add_test(tc, mult_number_small_values);
  tcase_add_test(tc, mult_number_negative_float);
  tcase_add_test(tc, mult_number_check_precision);

  suite_add_tcase(s, tc);
  return s;
}