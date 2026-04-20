#include <check.h>

#include "../../s21_matrix.h"

START_TEST(sub_3x3_positive) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = 6;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 8;
  A.matrix[1][1] = 9;
  A.matrix[1][2] = 10;
  A.matrix[2][0] = 11;
  A.matrix[2][1] = 12;
  A.matrix[2][2] = 13;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 6;
  B.matrix[2][0] = 7;
  B.matrix[2][1] = 8;
  B.matrix[2][2] = 9;

  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 4;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 4;
  expected.matrix[1][2] = 4;
  expected.matrix[2][0] = 4;
  expected.matrix[2][1] = 4;
  expected.matrix[2][2] = 4;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_3x3_negative) {
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

  expected.matrix[0][0] = 8;
  expected.matrix[0][1] = 6;
  expected.matrix[0][2] = 4;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 0;
  expected.matrix[1][2] = -2;
  expected.matrix[2][0] = -4;
  expected.matrix[2][1] = -6;
  expected.matrix[2][2] = -8;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_3x3_float) {
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

  expected.matrix[0][0] = 1.0;
  expected.matrix[0][1] = 1.0;
  expected.matrix[0][2] = 1.0;
  expected.matrix[1][0] = 1.0;
  expected.matrix[1][1] = 1.0;
  expected.matrix[1][2] = 1.0;
  expected.matrix[2][0] = 1.0;
  expected.matrix[2][1] = 1.0;
  expected.matrix[2][2] = 1.0;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_2x2_zero) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = 6;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 8;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 0;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_1x1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 10;
  B.matrix[0][0] = 3;
  expected.matrix[0][0] = 7;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_2x3) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(2, 3, &expected);

  A.matrix[0][0] = 10;
  A.matrix[0][1] = 20;
  A.matrix[0][2] = 30;
  A.matrix[1][0] = 40;
  A.matrix[1][1] = 50;
  A.matrix[1][2] = 60;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 6;

  expected.matrix[0][0] = 9;
  expected.matrix[0][1] = 18;
  expected.matrix[0][2] = 27;
  expected.matrix[1][0] = 36;
  expected.matrix[1][1] = 45;
  expected.matrix[1][2] = 54;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_4x1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(4, 1, &A);
  s21_create_matrix(4, 1, &B);
  s21_create_matrix(4, 1, &expected);

  A.matrix[0][0] = 10;
  A.matrix[1][0] = 20;
  A.matrix[2][0] = 30;
  A.matrix[3][0] = 40;

  B.matrix[0][0] = 1;
  B.matrix[1][0] = 2;
  B.matrix[2][0] = 3;
  B.matrix[3][0] = 4;

  expected.matrix[0][0] = 9;
  expected.matrix[1][0] = 18;
  expected.matrix[2][0] = 27;
  expected.matrix[3][0] = 36;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_1x4) {
  matrix_t A, B, result, expected;
  s21_create_matrix(1, 4, &A);
  s21_create_matrix(1, 4, &B);
  s21_create_matrix(1, 4, &expected);

  A.matrix[0][0] = 10;
  A.matrix[0][1] = 20;
  A.matrix[0][2] = 30;
  A.matrix[0][3] = 40;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[0][3] = 4;
  expected.matrix[0][0] = 9;
  expected.matrix[0][1] = 18;
  expected.matrix[0][2] = 27;
  expected.matrix[0][3] = 36;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_different_rows) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 3, &B);

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_different_columns) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 2, &B);

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_different_dimensions) {
  matrix_t A, B, result;
  s21_create_matrix(4, 3, &A);
  s21_create_matrix(3, 4, &B);

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_first_incorrect) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  s21_create_matrix(3, 3, &B);

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_second_incorrect) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);

  B.rows = 3;
  B.columns = -3;
  B.matrix = NULL;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sub_both_incorrect) {
  matrix_t A, B, result;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  B.rows = 3;
  B.columns = -1;
  B.matrix = NULL;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_null_A) {
  matrix_t B, result;
  s21_create_matrix(3, 3, &B);

  int code = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_null_B) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  int code = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sub_null_result) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  int code = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_large_values) {
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

  expected.matrix[0][0] = 500000;
  expected.matrix[0][1] = 1400000;
  expected.matrix[1][0] = 2300000;
  expected.matrix[1][1] = 3200000;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_small_values) {
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

  expected.matrix[0][0] = 0.0005;
  expected.matrix[0][1] = 0.0014;
  expected.matrix[1][0] = 0.0023;
  expected.matrix[1][1] = 0.0032;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_mixed_signs) {
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

  expected.matrix[0][0] = 7;
  expected.matrix[0][1] = -7;
  expected.matrix[1][0] = -13;
  expected.matrix[1][1] = 17;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);

  int eq = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *sub_suite(void) {
  Suite *s = suite_create("SUB");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sub_3x3_positive);
  tcase_add_test(tc, sub_3x3_negative);
  tcase_add_test(tc, sub_3x3_float);
  tcase_add_test(tc, sub_2x2_zero);
  tcase_add_test(tc, sub_1x1);
  tcase_add_test(tc, sub_2x3);
  tcase_add_test(tc, sub_4x1);
  tcase_add_test(tc, sub_1x4);
  tcase_add_test(tc, sub_different_rows);
  tcase_add_test(tc, sub_different_columns);
  tcase_add_test(tc, sub_different_dimensions);
  tcase_add_test(tc, sub_first_incorrect);
  tcase_add_test(tc, sub_second_incorrect);
  tcase_add_test(tc, sub_both_incorrect);
  tcase_add_test(tc, sub_null_A);
  tcase_add_test(tc, sub_null_B);
  tcase_add_test(tc, sub_null_result);
  tcase_add_test(tc, sub_large_values);
  tcase_add_test(tc, sub_small_values);
  tcase_add_test(tc, sub_mixed_signs);

  suite_add_tcase(s, tc);
  return s;
}