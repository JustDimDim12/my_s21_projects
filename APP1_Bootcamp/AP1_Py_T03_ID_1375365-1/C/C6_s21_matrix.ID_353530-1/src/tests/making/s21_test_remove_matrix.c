#include <check.h>
#include <stdlib.h>

#include "../../s21_matrix.h"

START_TEST(remove_normal_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[1][1] = 2.0;
  A.matrix[2][2] = 3.0;

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_null_matrix) {
  matrix_t A = {0};

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_with_null_rows) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  free(A.matrix[1]);
  A.matrix[1] = NULL;

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 42.0;

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_2x3) {
  matrix_t A;
  s21_create_matrix(2, 3, &A);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j;
    }
  }

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_5x5) {
  matrix_t A;
  s21_create_matrix(5, 5, &A);

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_already_removed_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  s21_remove_matrix(&A);
  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_with_negative_dimensions) {
  matrix_t A;
  A.rows = -1;
  A.columns = -1;
  A.matrix = NULL;

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_with_zero_dimensions) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_null_pointer) {
  matrix_t *A = NULL;

  s21_remove_matrix(A);

  ck_assert_ptr_null(A);
}
END_TEST

START_TEST(remove_large_matrix) {
  matrix_t A;
  s21_create_matrix(1000, 1000, &A);

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_check_memory_leak) {
  for (int k = 0; k < 100; k++) {
    matrix_t A;
    s21_create_matrix(10, 10, &A);

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        A.matrix[i][j] = i * 10 + j;
      }
    }

    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(remove_matrix_after_eq) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }

  int eq = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_ptr_null(A.matrix);
  ck_assert_ptr_null(B.matrix);
}
END_TEST

START_TEST(remove_matrix_after_sum) {
  matrix_t A, B, C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  s21_sum_matrix(&A, &B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_ptr_null(A.matrix);
  ck_assert_ptr_null(B.matrix);
  ck_assert_ptr_null(C.matrix);
}
END_TEST

START_TEST(remove_matrix_after_mult) {
  matrix_t A, B, C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 0;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 1;

  s21_mult_matrix(&A, &B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_ptr_null(A.matrix);
  ck_assert_ptr_null(B.matrix);
  ck_assert_ptr_null(C.matrix);
}
END_TEST

START_TEST(remove_matrix_after_transpose) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &A);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j;
    }
  }

  s21_transpose(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_ptr_null(A.matrix);
  ck_assert_ptr_null(B.matrix);
}
END_TEST

START_TEST(remove_matrix_after_calc_complements) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  s21_calc_complements(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_ptr_null(A.matrix);
  ck_assert_ptr_null(B.matrix);
}
END_TEST

Suite *remove_suite(void) {
  Suite *s = suite_create("REMOVE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, remove_normal_matrix);
  tcase_add_test(tc, remove_null_matrix);
  tcase_add_test(tc, remove_matrix_with_null_rows);

  tcase_add_test(tc, remove_matrix_1x1);
  tcase_add_test(tc, remove_matrix_2x3);
  tcase_add_test(tc, remove_matrix_5x5);

  tcase_add_test(tc, remove_already_removed_matrix);
  tcase_add_test(tc, remove_matrix_with_negative_dimensions);
  tcase_add_test(tc, remove_matrix_with_zero_dimensions);

  tcase_add_test(tc, remove_null_pointer);
  tcase_add_test(tc, remove_large_matrix);
  tcase_add_test(tc, remove_matrix_check_memory_leak);

  tcase_add_test(tc, remove_matrix_after_eq);
  tcase_add_test(tc, remove_matrix_after_sum);
  tcase_add_test(tc, remove_matrix_after_mult);
  tcase_add_test(tc, remove_matrix_after_transpose);
  tcase_add_test(tc, remove_matrix_after_calc_complements);

  suite_add_tcase(s, tc);
  return s;
}