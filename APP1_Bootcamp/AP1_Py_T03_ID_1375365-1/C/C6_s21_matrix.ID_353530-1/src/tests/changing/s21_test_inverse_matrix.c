#include <check.h>

#include "../../s21_matrix.h"

START_TEST(inverse_3x3) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_2x2) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  expected.matrix[0][0] = 0.6;
  expected.matrix[0][1] = -0.7;
  expected.matrix[1][0] = -0.2;
  expected.matrix[1][1] = 0.4;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_1x1) {
  matrix_t A, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 5;
  expected.matrix[0][0] = 0.2;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_identity_3x3) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 1;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 1;
  expected.matrix[1][2] = 0;
  expected.matrix[2][0] = 0;
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = 1;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_diagonal_3x3) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 8;

  expected.matrix[0][0] = 0.5;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 0.25;
  expected.matrix[1][2] = 0;
  expected.matrix[2][0] = 0;
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = 0.125;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_singular_matrix) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_not_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_incorrect_matrix) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_null_matrix) {
  matrix_t result;

  int code = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  int code = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_2x2_float) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[1][0] = 3.5;
  A.matrix[1][1] = 4.5;

  double det = 1.5 * 4.5 - 2.5 * 3.5;
  expected.matrix[0][0] = 4.5 / det;
  expected.matrix[0][1] = -2.5 / det;
  expected.matrix[1][0] = -3.5 / det;
  expected.matrix[1][1] = 1.5 / det;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_3x3_float) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 0.0;

  expected.matrix[0][0] = -24.0 / 53.0;
  expected.matrix[0][1] = 18.0 / 53.0;
  expected.matrix[0][2] = 5.0 / 53.0;
  expected.matrix[1][0] = 20.0 / 53.0;
  expected.matrix[1][1] = -15.0 / 53.0;
  expected.matrix[1][2] = -4.0 / 53.0;
  expected.matrix[2][0] = -5.0 / 53.0;
  expected.matrix[2][1] = 4.0 / 53.0;
  expected.matrix[2][2] = 1.0 / 53.0;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_3x3_negative) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = -9;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_check_AB) {
  matrix_t A, B, result, mult;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 0;
  B.matrix[0][2] = 0;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 1;
  B.matrix[1][2] = 0;
  B.matrix[2][0] = 0;
  B.matrix[2][1] = 0;
  B.matrix[2][2] = 1;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  s21_mult_matrix(&A, &result, &mult);

  int eq = s21_eq_matrix(&mult, &B);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&mult);
}
END_TEST

START_TEST(inverse_large_values) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1000;
  A.matrix[0][1] = 500;
  A.matrix[1][0] = 200;
  A.matrix[1][1] = 300;

  double det = 1000 * 300 - 500 * 200;
  expected.matrix[0][0] = 300 / det;
  expected.matrix[0][1] = -500 / det;
  expected.matrix[1][0] = -200 / det;
  expected.matrix[1][1] = 1000 / det;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_zero_det) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

Suite *inverse_suite(void) {
  Suite *s = suite_create("INVERSE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, inverse_3x3);
  tcase_add_test(tc, inverse_2x2);
  tcase_add_test(tc, inverse_1x1);
  tcase_add_test(tc, inverse_identity_3x3);
  tcase_add_test(tc, inverse_diagonal_3x3);
  tcase_add_test(tc, inverse_singular_matrix);
  tcase_add_test(tc, inverse_not_square);
  tcase_add_test(tc, inverse_incorrect_matrix);
  tcase_add_test(tc, inverse_null_matrix);
  tcase_add_test(tc, inverse_null_result);
  tcase_add_test(tc, inverse_2x2_float);
  tcase_add_test(tc, inverse_3x3_float);
  tcase_add_test(tc, inverse_3x3_negative);
  tcase_add_test(tc, inverse_check_AB);
  tcase_add_test(tc, inverse_large_values);
  tcase_add_test(tc, inverse_zero_det);

  suite_add_tcase(s, tc);
  return s;
}