#include <check.h>

#include "../../s21_decimal.h"

START_TEST(less_or_equal_test_1_less_true) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  int res = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // 1 < 2 => true
}
END_TEST

START_TEST(less_or_equal_test_2_equal_true) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int res = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // 5 == 5 => true
}
END_TEST

START_TEST(less_or_equal_test_3_greater_false) {
  s21_decimal a = {{7, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  int res = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(res, 0);  // 7 <= 3 => false
}
END_TEST

START_TEST(less_or_equal_test_4_negative_numbers) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal b = {{3, 0, 0, 0x80000000}};  // -3
  int res = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // -5 <= -3 => true
}
END_TEST

START_TEST(less_or_equal_test_5_equal_with_scale) {
  s21_decimal a = {{100, 0, 0, 2 << 16}};  // 1.00
  s21_decimal b = {{10, 0, 0, 1 << 16}};   // 1.0
  int res = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // 1.00 == 1.0 => true
}
END_TEST

Suite *is_less_or_equal_suite(void) {
  Suite *s = suite_create("LESS_OR_EQUAL");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, less_or_equal_test_1_less_true);
  tcase_add_test(tc, less_or_equal_test_2_equal_true);
  tcase_add_test(tc, less_or_equal_test_3_greater_false);
  tcase_add_test(tc, less_or_equal_test_4_negative_numbers);
  tcase_add_test(tc, less_or_equal_test_5_equal_with_scale);

  suite_add_tcase(s, tc);
  return s;
}