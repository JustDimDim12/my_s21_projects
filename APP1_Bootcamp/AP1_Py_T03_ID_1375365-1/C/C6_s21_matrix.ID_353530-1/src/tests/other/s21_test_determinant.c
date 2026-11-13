#include <check.h>

#include "../../s21_matrix.h"

START_TEST(determinant_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  double result = 0;

  A.matrix[0][0] = 5;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 5.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_1x1_negative) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  double result = 0;

  A.matrix[0][0] = -3.5;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, -3.5, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2x2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  double result = 0;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, -2.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2x2_float) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  double result = 0;

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[1][0] = 3.5;
  A.matrix[1][1] = 4.5;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 1.5 * 4.5 - 2.5 * 3.5, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2x2_negative) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  double result = 0;

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, (-1) * (-4) - (-2) * (-3), 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2x2_zero) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  double result = 0;

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3x3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3x3_positive) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, -1.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3x3_float) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = 1.2;
  A.matrix[0][1] = 2.3;
  A.matrix[0][2] = 3.4;
  A.matrix[1][0] = 4.5;
  A.matrix[1][1] = 5.6;
  A.matrix[1][2] = 6.7;
  A.matrix[2][0] = 7.8;
  A.matrix[2][1] = 8.9;
  A.matrix[2][2] = 9.1;

  double expected = 1.2 * (5.6 * 9.1 - 6.7 * 8.9) -
                    2.3 * (4.5 * 9.1 - 6.7 * 7.8) +
                    3.4 * (4.5 * 8.9 - 5.6 * 7.8);

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, expected, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3x3_negative) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = -1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = -9;

  double expected = -1 * ((-5) * (-9) - 6 * 8) - 2 * (4 * (-9) - 6 * (-7)) +
                    (-3) * (4 * 8 - (-5) * (-7));

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, expected, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4x4) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  double result = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i * 4 + j + 1;
    }
  }

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4x4_nonzero) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  double result = 0;

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 4;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;
  A.matrix[2][3] = 5;
  A.matrix[3][0] = 4;
  A.matrix[3][1] = 4;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = 6;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, -1.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_identity) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  double result = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = (i == j) ? 1 : 0;
    }
  }

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 1.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_diagonal) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 4;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 24.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_upper_triangular) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 2 * 3 * 6, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_lower_triangular) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 6;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 4 * 5 * 6, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_not_square) {
  matrix_t A;
  s21_create_matrix(2, 3, &A);
  double result = 0;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_incorrect_matrix) {
  matrix_t A;
  double result = 0;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_null_matrix) {
  double result = 0;

  int code = s21_determinant(NULL, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int code = s21_determinant(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_zero_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0;
    }
  }

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_singular) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double result = 0;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 9;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_large_values) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  double result = 0;

  A.matrix[0][0] = 1000000.0;
  A.matrix[0][1] = 500000.0;
  A.matrix[1][0] = 200000.0;
  A.matrix[1][1] = 300000.0;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 1000000.0 * 300000.0 - 500000.0 * 200000.0,
                          1e-7);

  s21_remove_matrix(&A);
}
END_TEST

Suite *determinant_suite(void) {
  Suite *s = suite_create("DETERMINANT");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, determinant_1x1);
  tcase_add_test(tc, determinant_1x1_negative);
  tcase_add_test(tc, determinant_2x2);
  tcase_add_test(tc, determinant_2x2_float);
  tcase_add_test(tc, determinant_2x2_negative);
  tcase_add_test(tc, determinant_2x2_zero);
  tcase_add_test(tc, determinant_3x3);
  tcase_add_test(tc, determinant_3x3_positive);
  tcase_add_test(tc, determinant_3x3_float);
  tcase_add_test(tc, determinant_3x3_negative);
  tcase_add_test(tc, determinant_4x4);
  tcase_add_test(tc, determinant_4x4_nonzero);
  tcase_add_test(tc, determinant_identity);
  tcase_add_test(tc, determinant_diagonal);
  tcase_add_test(tc, determinant_upper_triangular);
  tcase_add_test(tc, determinant_lower_triangular);
  tcase_add_test(tc, determinant_not_square);
  tcase_add_test(tc, determinant_incorrect_matrix);
  tcase_add_test(tc, determinant_null_matrix);
  tcase_add_test(tc, determinant_null_result);
  tcase_add_test(tc, determinant_zero_matrix);
  tcase_add_test(tc, determinant_singular);
  tcase_add_test(tc, determinant_large_values);

  suite_add_tcase(s, tc);
  return s;
}