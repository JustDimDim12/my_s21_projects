#include <check.h>

#include "../../s21_matrix.h"

START_TEST(rows_less_than_one) {
  matrix_t a;
  int code = s21_create_matrix(-1, 2, &a);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(columns_less_than_one) {
  matrix_t a;
  int code = s21_create_matrix(4, 0, &a);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(both_less_than_one) {
  matrix_t a;
  int code = s21_create_matrix(-5, -3, &a);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(rows_zero) {
  matrix_t a;
  int code = s21_create_matrix(0, 5, &a);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(columns_zero) {
  matrix_t a;
  int code = s21_create_matrix(3, 0, &a);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_1x1) {
  matrix_t a;
  int code = s21_create_matrix(1, 1, &a);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(a.rows, 1);
  ck_assert_int_eq(a.columns, 1);
  ck_assert_ptr_nonnull(a.matrix);
  ck_assert_ptr_nonnull(a.matrix[0]);

  ck_assert_double_eq_tol(a.matrix[0][0], 0.0, 1e-7);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_2x2) {
  matrix_t a;
  int code = s21_create_matrix(2, 2, &a);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(a.rows, 2);
  ck_assert_int_eq(a.columns, 2);
  ck_assert_ptr_nonnull(a.matrix);

  for (int i = 0; i < 2; i++) {
    ck_assert_ptr_nonnull(a.matrix[i]);
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(a.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_3x3) {
  matrix_t a;
  int code = s21_create_matrix(3, 3, &a);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(a.rows, 3);
  ck_assert_int_eq(a.columns, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(a.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_5x3) {
  matrix_t a;
  int code = s21_create_matrix(5, 3, &a);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(a.rows, 5);
  ck_assert_int_eq(a.columns, 3);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(a.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_3x5) {
  matrix_t a;
  int code = s21_create_matrix(3, 5, &a);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(a.rows, 3);
  ck_assert_int_eq(a.columns, 5);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      ck_assert_double_eq_tol(a.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_10x10) {
  matrix_t a;
  int code = s21_create_matrix(10, 10, &a);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(a.rows, 10);
  ck_assert_int_eq(a.columns, 10);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ck_assert_double_eq_tol(a.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_100x100) {
  matrix_t a;
  int code = s21_create_matrix(100, 100, &a);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(a.rows, 100);
  ck_assert_int_eq(a.columns, 100);

  ck_assert_double_eq_tol(a.matrix[0][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(a.matrix[50][50], 0.0, 1e-7);
  ck_assert_double_eq_tol(a.matrix[99][99], 0.0, 1e-7);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_max_size) {
  matrix_t a;
  int code = s21_create_matrix(1000, 1000, &a);

  if (code == OK) {
    ck_assert_int_eq(a.rows, 1000);
    ck_assert_int_eq(a.columns, 1000);
    s21_remove_matrix(&a);
  }
}
END_TEST

START_TEST(null_result_pointer) {
  int code = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(memory_allocation_check) {
  matrix_t a;
  int code = s21_create_matrix(4, 4, &a);

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      ck_assert_ptr_ne(a.matrix[i], a.matrix[j]);
    }
  }

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(multiple_create_remove) {
  for (int k = 0; k < 10; k++) {
    matrix_t a;
    int code = s21_create_matrix(5, 5, &a);
    ck_assert_int_eq(code, OK);

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        a.matrix[i][j] = i * 5 + j;
      }
    }

    s21_remove_matrix(&a);
  }
}
END_TEST

START_TEST(zero_initialization) {
  matrix_t a;
  int code = s21_create_matrix(3, 4, &a);

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq_tol(a.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_calloc_fail) {
  matrix_t result;

  int code = s21_create_matrix(1000000000, 1000000000, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

Suite *create_suite(void) {
  Suite *s = suite_create("CREATE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, rows_less_than_one);
  tcase_add_test(tc, columns_less_than_one);
  tcase_add_test(tc, both_less_than_one);
  tcase_add_test(tc, rows_zero);
  tcase_add_test(tc, columns_zero);
  tcase_add_test(tc, null_result_pointer);
  tcase_add_test(tc, create_matrix_1x1);
  tcase_add_test(tc, create_matrix_2x2);
  tcase_add_test(tc, create_matrix_3x3);
  tcase_add_test(tc, create_matrix_5x3);
  tcase_add_test(tc, create_matrix_3x5);
  tcase_add_test(tc, create_matrix_10x10);
  tcase_add_test(tc, create_matrix_100x100);
  tcase_add_test(tc, create_matrix_max_size);
  tcase_add_test(tc, memory_allocation_check);
  tcase_add_test(tc, multiple_create_remove);
  tcase_add_test(tc, zero_initialization);
  tcase_add_test(tc, create_matrix_calloc_fail);
  suite_add_tcase(s, tc);
  return s;
}