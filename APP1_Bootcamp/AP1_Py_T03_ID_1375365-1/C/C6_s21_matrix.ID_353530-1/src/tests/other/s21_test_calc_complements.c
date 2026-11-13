#include <check.h>

#include "../../s21_matrix.h"

START_TEST(calc_complements_3x3) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_2x2) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = -3;
  expected.matrix[1][0] = -2;
  expected.matrix[1][1] = 1;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_1x1) {
  matrix_t A, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 5;
  expected.matrix[0][0] = 1;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_identity_3x3) {
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

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_diagonal_3x3) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 4;

  expected.matrix[0][0] = 12;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 8;
  expected.matrix[1][2] = 0;
  expected.matrix[2][0] = 0;
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = 6;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_float) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[1][0] = 3.5;
  A.matrix[1][1] = 4.5;

  expected.matrix[0][0] = 4.5;
  expected.matrix[0][1] = -3.5;
  expected.matrix[1][0] = -2.5;
  expected.matrix[1][1] = 1.5;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_negative) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  expected.matrix[0][0] = -4;
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = -1;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_not_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_incorrect_matrix) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(calc_complements_null_matrix) {
  matrix_t result;

  int code = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(calc_complements_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int code = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_zero_matrix) {
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

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_singular) {
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

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_3x3_float) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1.2;
  A.matrix[0][1] = 2.3;
  A.matrix[0][2] = 3.4;
  A.matrix[1][0] = 4.5;
  A.matrix[1][1] = 5.6;
  A.matrix[1][2] = 6.7;
  A.matrix[2][0] = 7.8;
  A.matrix[2][1] = 8.9;
  A.matrix[2][2] = 9.1;

  expected.matrix[0][0] = 5.6 * 9.1 - 6.7 * 8.9;
  expected.matrix[0][1] = -(4.5 * 9.1 - 6.7 * 7.8);
  expected.matrix[0][2] = 4.5 * 8.9 - 5.6 * 7.8;
  expected.matrix[1][0] = -(2.3 * 9.1 - 3.4 * 8.9);
  expected.matrix[1][1] = 1.2 * 9.1 - 3.4 * 7.8;
  expected.matrix[1][2] = -(1.2 * 8.9 - 2.3 * 7.8);
  expected.matrix[2][0] = 2.3 * 6.7 - 3.4 * 5.6;
  expected.matrix[2][1] = -(1.2 * 6.7 - 3.4 * 4.5);
  expected.matrix[2][2] = 1.2 * 5.6 - 2.3 * 4.5;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_check_signs) {
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

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      ck_assert_double_eq_tol(result.matrix[i][j], sign * expected.matrix[i][j],
                              1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_4x4) {
  matrix_t A, result;
  s21_create_matrix(4, 4, &A);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i * 4 + j + 1;
    }
  }

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *calc_complements_suite(void) {
  Suite *s = suite_create("CALC_COMPLEMENTS");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, calc_complements_3x3);
  tcase_add_test(tc, calc_complements_2x2);
  tcase_add_test(tc, calc_complements_1x1);
  tcase_add_test(tc, calc_complements_identity_3x3);
  tcase_add_test(tc, calc_complements_diagonal_3x3);
  tcase_add_test(tc, calc_complements_float);
  tcase_add_test(tc, calc_complements_negative);
  tcase_add_test(tc, calc_complements_not_square);
  tcase_add_test(tc, calc_complements_incorrect_matrix);
  tcase_add_test(tc, calc_complements_null_matrix);
  tcase_add_test(tc, calc_complements_null_result);
  tcase_add_test(tc, calc_complements_zero_matrix);
  tcase_add_test(tc, calc_complements_singular);
  tcase_add_test(tc, calc_complements_3x3_float);
  tcase_add_test(tc, calc_complements_check_signs);
  tcase_add_test(tc, calc_complements_4x4);

  suite_add_tcase(s, tc);
  return s;
}