#include <check.h>

#include "../../s21_matrix.h"

START_TEST(eq_equal_matrices_3x3) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double value = i * 3 + j + 1;
      A.matrix[i][j] = value;
      B.matrix[i][j] = value;
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_equal_matrices_2x4) {
  matrix_t A, B;
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(2, 4, &B);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      double value = (i + 1) * (j + 1) * 1.5;
      A.matrix[i][j] = value;
      B.matrix[i][j] = value;
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_equal_matrices_1x1) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 3.14159;
  B.matrix[0][0] = 3.14159;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_equal_matrices_with_precision) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 0.12345678;
  A.matrix[0][1] = 0.12345678;
  A.matrix[1][0] = 0.12345678;
  A.matrix[1][1] = 0.12345678;

  B.matrix[0][0] = 0.12345678;
  B.matrix[0][1] = 0.12345678;
  B.matrix[1][0] = 0.12345678;
  B.matrix[1][1] = 0.12345678;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_different_matrices_3x3) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
      B.matrix[i][j] = i * 3 + j + 2;
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_different_matrices_one_element) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 5;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_different_matrices_precision_edge) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 0.12345678;
  B.matrix[0][0] = 0.12345679;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_different_matrices_precision_within) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 0.12345678;
  B.matrix[0][0] = 0.12345678 + 1e-8;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_different_rows) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 3, &B);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_different_columns) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 2, &B);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_different_dimensions) {
  matrix_t A, B;
  s21_create_matrix(4, 3, &A);
  s21_create_matrix(3, 4, &B);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_one_matrix_incorrect) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  B.rows = 3;
  B.columns = 3;
  B.matrix = NULL;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_both_matrices_incorrect) {
  matrix_t A, B;
  A.rows = -1;
  A.columns = 3;
  A.matrix = NULL;

  B.rows = 3;
  B.columns = -1;
  B.matrix = NULL;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(eq_null_matrix_first) {
  matrix_t B;
  s21_create_matrix(3, 3, &B);

  int result = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_null_matrix_second) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  int result = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_both_null) {
  int result = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(eq_matrix_with_negative_values) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1.5;
  A.matrix[0][1] = -2.5;
  A.matrix[1][0] = -3.5;
  A.matrix[1][1] = -4.5;

  B.matrix[0][0] = -1.5;
  B.matrix[0][1] = -2.5;
  B.matrix[1][0] = -3.5;
  B.matrix[1][1] = -4.5;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_with_zero_values) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0;
      B.matrix[i][j] = 0;
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_very_small_values) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1e-10;
  A.matrix[0][1] = 2e-10;
  A.matrix[1][0] = 3e-10;
  A.matrix[1][1] = 4e-10;

  B.matrix[0][0] = 1e-10;
  B.matrix[0][1] = 2e-10;
  B.matrix[1][0] = 3e-10;
  B.matrix[1][1] = 4e-10;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_very_large_values) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1e10;
  A.matrix[0][1] = 2e10;
  A.matrix[1][0] = 3e10;
  A.matrix[1][1] = 4e10;

  B.matrix[0][0] = 1e10;
  B.matrix[0][1] = 2e10;
  B.matrix[1][0] = 3e10;
  B.matrix[1][1] = 4e10;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *eq_suite(void) {
  Suite *s = suite_create("EQ");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, eq_equal_matrices_3x3);
  tcase_add_test(tc, eq_equal_matrices_2x4);
  tcase_add_test(tc, eq_equal_matrices_1x1);
  tcase_add_test(tc, eq_equal_matrices_with_precision);
  tcase_add_test(tc, eq_different_matrices_3x3);
  tcase_add_test(tc, eq_different_matrices_one_element);
  tcase_add_test(tc, eq_different_matrices_precision_edge);
  tcase_add_test(tc, eq_different_matrices_precision_within);
  tcase_add_test(tc, eq_different_rows);
  tcase_add_test(tc, eq_different_columns);
  tcase_add_test(tc, eq_different_dimensions);
  tcase_add_test(tc, eq_one_matrix_incorrect);
  tcase_add_test(tc, eq_both_matrices_incorrect);
  tcase_add_test(tc, eq_null_matrix_first);
  tcase_add_test(tc, eq_null_matrix_second);
  tcase_add_test(tc, eq_both_null);
  tcase_add_test(tc, eq_matrix_with_negative_values);
  tcase_add_test(tc, eq_matrix_with_zero_values);
  tcase_add_test(tc, eq_matrix_very_small_values);
  tcase_add_test(tc, eq_matrix_very_large_values);

  suite_add_tcase(s, tc);
  return s;
}