#include <check.h>

#include "../../s21_matrix.h"

START_TEST(sum_3x3_positive) {
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

  expected.matrix[0][0] = 10;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = 10;
  expected.matrix[1][0] = 10;
  expected.matrix[1][1] = 10;
  expected.matrix[1][2] = 10;
  expected.matrix[2][0] = 10;
  expected.matrix[2][1] = 10;
  expected.matrix[2][2] = 10;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_3x3_negative) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = -8;
  A.matrix[2][2] = -9;

  B.matrix[0][0] = -9;
  B.matrix[0][1] = -8;
  B.matrix[0][2] = -7;
  B.matrix[1][0] = -6;
  B.matrix[1][1] = -5;
  B.matrix[1][2] = -4;
  B.matrix[2][0] = -3;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = -1;

  expected.matrix[0][0] = -10;
  expected.matrix[0][1] = -10;
  expected.matrix[0][2] = -10;
  expected.matrix[1][0] = -10;
  expected.matrix[1][1] = -10;
  expected.matrix[1][2] = -10;
  expected.matrix[2][0] = -10;
  expected.matrix[2][1] = -10;
  expected.matrix[2][2] = -10;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_3x3_float) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
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

  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 1.5;
  B.matrix[0][2] = 2.5;
  B.matrix[1][0] = 3.5;
  B.matrix[1][1] = 4.5;
  B.matrix[1][2] = 5.5;
  B.matrix[2][0] = 6.5;
  B.matrix[2][1] = 7.5;
  B.matrix[2][2] = 8.5;

  expected.matrix[0][0] = 2.0;
  expected.matrix[0][1] = 4.0;
  expected.matrix[0][2] = 6.0;
  expected.matrix[1][0] = 8.0;
  expected.matrix[1][1] = 10.0;
  expected.matrix[1][2] = 12.0;
  expected.matrix[2][0] = 14.0;
  expected.matrix[2][1] = 16.0;
  expected.matrix[2][2] = 18.0;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_2x2_zero) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = 6;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 8;

  B.matrix[0][0] = -5;
  B.matrix[0][1] = -6;
  B.matrix[1][0] = -7;
  B.matrix[1][1] = -8;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 0;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_1x1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 5;
  B.matrix[0][0] = 7;
  expected.matrix[0][0] = 12;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_2x3) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(2, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  B.matrix[0][0] = 6;
  B.matrix[0][1] = 5;
  B.matrix[0][2] = 4;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = 1;

  expected.matrix[0][0] = 7;
  expected.matrix[0][1] = 7;
  expected.matrix[0][2] = 7;
  expected.matrix[1][0] = 7;
  expected.matrix[1][1] = 7;
  expected.matrix[1][2] = 7;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_4x1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(4, 1, &A);
  s21_create_matrix(4, 1, &B);
  s21_create_matrix(4, 1, &expected);

  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[3][0] = 4;

  B.matrix[0][0] = 5;
  B.matrix[1][0] = 6;
  B.matrix[2][0] = 7;
  B.matrix[3][0] = 8;

  expected.matrix[0][0] = 6;
  expected.matrix[1][0] = 8;
  expected.matrix[2][0] = 10;
  expected.matrix[3][0] = 12;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_1x4) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 4, &A);
  s21_create_matrix(1, 4, &B);
  s21_create_matrix(1, 4, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[0][2] = 7;
  B.matrix[0][3] = 8;
  expected.matrix[0][0] = 6;
  expected.matrix[0][1] = 8;
  expected.matrix[0][2] = 10;
  expected.matrix[0][3] = 12;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_different_rows) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 3, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_different_columns) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 2, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_different_dimensions) {
  matrix_t A, B, result;
  s21_create_matrix(4, 3, &A);
  s21_create_matrix(3, 4, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_first_incorrect) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  s21_create_matrix(3, 3, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_second_incorrect) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);

  B.rows = 3;
  B.columns = -3;
  B.matrix = NULL;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sum_both_incorrect) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  B.rows = 3;
  B.columns = -1;
  B.matrix = NULL;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sum_null_A) {
  matrix_t B, result;
  s21_create_matrix(3, 3, &B);

  int code = s21_sum_matrix(NULL, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_null_B) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  int code = s21_sum_matrix(&A, NULL, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sum_null_result) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  int code = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_large_values) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1000000;
  A.matrix[0][1] = 2000000;
  A.matrix[1][0] = 3000000;
  A.matrix[1][1] = 4000000;

  B.matrix[0][0] = 500000;
  B.matrix[0][1] = 600000;
  B.matrix[1][0] = 700000;
  B.matrix[1][1] = 800000;

  expected.matrix[0][0] = 1500000;
  expected.matrix[0][1] = 2600000;
  expected.matrix[1][0] = 3700000;
  expected.matrix[1][1] = 4800000;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_small_values) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 0.001;
  A.matrix[0][1] = 0.002;
  A.matrix[1][0] = 0.003;
  A.matrix[1][1] = 0.004;

  B.matrix[0][0] = 0.0005;
  B.matrix[0][1] = 0.0006;
  B.matrix[1][0] = 0.0007;
  B.matrix[1][1] = 0.0008;

  expected.matrix[0][0] = 0.0015;
  expected.matrix[0][1] = 0.0026;
  expected.matrix[1][0] = 0.0037;
  expected.matrix[1][1] = 0.0048;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_mixed_signs) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = -3;
  A.matrix[1][0] = -7;
  A.matrix[1][1] = 9;

  B.matrix[0][0] = -2;
  B.matrix[0][1] = 4;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = -8;

  expected.matrix[0][0] = 3;
  expected.matrix[0][1] = 1;
  expected.matrix[1][0] = -1;
  expected.matrix[1][1] = 1;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sum_precision_check) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 0.12345678;
  B.matrix[0][0] = 0.12345678;
  expected.matrix[0][0] = 0.24691356;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *sum_suite(void) {
  Suite *s = suite_create("SUM");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sum_3x3_positive);
  tcase_add_test(tc, sum_3x3_negative);
  tcase_add_test(tc, sum_3x3_float);
  tcase_add_test(tc, sum_2x2_zero);
  tcase_add_test(tc, sum_1x1);
  tcase_add_test(tc, sum_2x3);
  tcase_add_test(tc, sum_4x1);
  tcase_add_test(tc, sum_1x4);
  tcase_add_test(tc, sum_different_rows);
  tcase_add_test(tc, sum_different_columns);
  tcase_add_test(tc, sum_different_dimensions);
  tcase_add_test(tc, sum_first_incorrect);
  tcase_add_test(tc, sum_second_incorrect);
  tcase_add_test(tc, sum_both_incorrect);
  tcase_add_test(tc, sum_null_A);
  tcase_add_test(tc, sum_null_B);
  tcase_add_test(tc, sum_null_result);
  tcase_add_test(tc, sum_large_values);
  tcase_add_test(tc, sum_small_values);
  tcase_add_test(tc, sum_mixed_signs);
  tcase_add_test(tc, sum_precision_check);

  suite_add_tcase(s, tc);
  return s;
}