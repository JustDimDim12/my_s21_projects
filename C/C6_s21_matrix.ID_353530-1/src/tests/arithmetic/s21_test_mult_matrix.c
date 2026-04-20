#include <check.h>

#include "../../s21_matrix.h"

START_TEST(mult_matrix_3x3_3x3) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
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

  B.matrix[0][0] = 9;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 4;
  B.matrix[2][0] = 3;
  B.matrix[2][1] = 2;
  B.matrix[2][2] = 1;

  expected.matrix[0][0] = 30;
  expected.matrix[0][1] = 24;
  expected.matrix[0][2] = 18;
  expected.matrix[1][0] = 84;
  expected.matrix[1][1] = 69;
  expected.matrix[1][2] = 54;
  expected.matrix[2][0] = 138;
  expected.matrix[2][1] = 114;
  expected.matrix[2][2] = 90;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_2x3_3x2) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  B.matrix[0][0] = 7;
  B.matrix[0][1] = 8;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 10;
  B.matrix[2][0] = 11;
  B.matrix[2][1] = 12;

  expected.matrix[0][0] = 58;
  expected.matrix[0][1] = 64;
  expected.matrix[1][0] = 139;
  expected.matrix[1][1] = 154;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_1x3_3x1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  B.matrix[0][0] = 4;
  B.matrix[1][0] = 5;
  B.matrix[2][0] = 6;

  expected.matrix[0][0] = 32;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_3x1_1x3) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(1, 3, &B);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;

  B.matrix[0][0] = 4;
  B.matrix[0][1] = 5;
  B.matrix[0][2] = 6;

  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = 5;
  expected.matrix[0][2] = 6;
  expected.matrix[1][0] = 8;
  expected.matrix[1][1] = 10;
  expected.matrix[1][2] = 12;
  expected.matrix[2][0] = 12;
  expected.matrix[2][1] = 15;
  expected.matrix[2][2] = 18;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_identity) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
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

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 0;
  B.matrix[0][2] = 0;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 1;
  B.matrix[1][2] = 0;
  B.matrix[2][0] = 0;
  B.matrix[2][1] = 0;
  B.matrix[2][2] = 1;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 6;
  expected.matrix[2][0] = 7;
  expected.matrix[2][1] = 8;
  expected.matrix[2][2] = 9;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_zero_matrix) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 0;
  B.matrix[0][1] = 0;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 0;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 0;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_incompatible_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_first_incorrect) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  s21_create_matrix(3, 2, &B);

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_second_incorrect) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);

  B.rows = 3;
  B.columns = -2;
  B.matrix = NULL;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_both_incorrect) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  B.rows = 3;
  B.columns = -2;
  B.matrix = NULL;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(mult_matrix_null_result) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  int code = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_1x1_1x1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 5;
  B.matrix[0][0] = 7;
  expected.matrix[0][0] = 35;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_float_values) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[1][0] = 3.5;
  A.matrix[1][1] = 4.5;

  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 1.5;
  B.matrix[1][0] = 2.5;
  B.matrix[1][1] = 3.5;

  expected.matrix[0][0] = 1.5 * 0.5 + 2.5 * 2.5;
  expected.matrix[0][1] = 1.5 * 1.5 + 2.5 * 3.5;
  expected.matrix[1][0] = 3.5 * 0.5 + 4.5 * 2.5;
  expected.matrix[1][1] = 3.5 * 1.5 + 4.5 * 3.5;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_negative_values) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  B.matrix[0][0] = -5;
  B.matrix[0][1] = -6;
  B.matrix[1][0] = -7;
  B.matrix[1][1] = -8;

  expected.matrix[0][0] = 19;
  expected.matrix[0][1] = 22;
  expected.matrix[1][0] = 43;
  expected.matrix[1][1] = 50;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_large_values) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1000;
  A.matrix[0][1] = 2000;
  A.matrix[1][0] = 3000;
  A.matrix[1][1] = 4000;

  B.matrix[0][0] = 5000;
  B.matrix[0][1] = 6000;
  B.matrix[1][0] = 7000;
  B.matrix[1][1] = 8000;

  expected.matrix[0][0] = 1000 * 5000 + 2000 * 7000;
  expected.matrix[0][1] = 1000 * 6000 + 2000 * 8000;
  expected.matrix[1][0] = 3000 * 5000 + 4000 * 7000;
  expected.matrix[1][1] = 3000 * 6000 + 4000 * 8000;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *mult_matrix_suite(void) {
  Suite *s = suite_create("MULT_MATRIX");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, mult_matrix_3x3_3x3);
  tcase_add_test(tc, mult_matrix_2x3_3x2);
  tcase_add_test(tc, mult_matrix_1x3_3x1);
  tcase_add_test(tc, mult_matrix_3x1_1x3);
  tcase_add_test(tc, mult_matrix_identity);
  tcase_add_test(tc, mult_matrix_zero_matrix);
  tcase_add_test(tc, mult_matrix_incompatible_sizes);
  tcase_add_test(tc, mult_matrix_first_incorrect);
  tcase_add_test(tc, mult_matrix_second_incorrect);
  tcase_add_test(tc, mult_matrix_both_incorrect);
  tcase_add_test(tc, mult_matrix_null_result);
  tcase_add_test(tc, mult_matrix_1x1_1x1);
  tcase_add_test(tc, mult_matrix_float_values);
  tcase_add_test(tc, mult_matrix_negative_values);
  tcase_add_test(tc, mult_matrix_large_values);

  suite_add_tcase(s, tc);
  return s;
}