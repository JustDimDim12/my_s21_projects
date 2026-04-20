#include <check.h>

#include "../../s21_decimal.h"

// ------------------------ TEST CASES ------------------------

START_TEST(mul_simple_positive) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal res;

  int code = s21_mul(a, b, &res);
  ck_assert_int_eq(code, 0);

  s21_decimal expected = {{6, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(mul_with_zero) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res;

  int code = s21_mul(a, b, &res);
  ck_assert_int_eq(code, 0);

  s21_decimal expected = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(mul_negative_result) {
  s21_decimal a = {{2, 0, 0, 2147483648u}};  // -2
  s21_decimal b = {{3, 0, 0, 0}};            // 3
  s21_decimal res;

  int code = s21_mul(a, b, &res);
  ck_assert_int_eq(code, 0);

  s21_decimal expected = {{6, 0, 0, 2147483648u}};  // -6
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(mul_two_negatives) {
  s21_decimal a = {{2, 0, 0, 2147483648u}};  // -2
  s21_decimal b = {{3, 0, 0, 2147483648u}};  // -3
  s21_decimal res;

  int code = s21_mul(a, b, &res);
  ck_assert_int_eq(code, 0);

  s21_decimal expected = {{6, 0, 0, 0}};  // 6
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(mul_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res;

  int code = s21_mul(a, b, &res);
  ck_assert_int_ne(code, 0);  // Любая ненулевая ошибка - переполнение
}
END_TEST

// ------------------------ SUITE ------------------------

Suite* suite_s21_mul(void) {
  Suite* s = suite_create("s21_mul");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, mul_simple_positive);
  tcase_add_test(tc_core, mul_with_zero);
  tcase_add_test(tc_core, mul_negative_result);
  tcase_add_test(tc_core, mul_two_negatives);
  tcase_add_test(tc_core, mul_overflow);

  suite_add_tcase(s, tc_core);
  return s;
}
