#include <check.h>

#include "../../s21_decimal.h"

START_TEST(greater_or_equal_test_1_basic_true) {
  s21_decimal a = {{5, 0, 0, 0}};  // 5
  s21_decimal b = {{3, 0, 0, 0}};  // 3
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // 5 ≥ 3 => true
}
END_TEST

START_TEST(greater_or_equal_test_2_equal_values) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // 5 ≥ 5 => true
}
END_TEST

START_TEST(greater_or_equal_test_3_less_false) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 0);  // 3 ≥ 5 => false
}
END_TEST

START_TEST(greater_or_equal_test_4_positive_vs_negative) {
  s21_decimal a = {{2, 0, 0, 0}};           // +2
  s21_decimal b = {{2, 0, 0, 0x80000000}};  // -2
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // +2 ≥ -2 => true
}
END_TEST

START_TEST(greater_or_equal_test_5_negative_vs_positive) {
  s21_decimal a = {{2, 0, 0, 0x80000000}};  // -2
  s21_decimal b = {{2, 0, 0, 0}};           // +2
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 0);  // -2 ≥ +2 => false
}
END_TEST

START_TEST(greater_or_equal_test_6_different_scales_equal) {
  s21_decimal a = {{1, 0, 0, 0}};         // 1
  s21_decimal b = {{10, 0, 0, 1 << 16}};  // 1.0
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // 1 ≥ 1.0 => true
}
END_TEST

START_TEST(greater_or_equal_test_7_different_scales_greater) {
  s21_decimal a = {{121, 0, 0, 2 << 16}};  // 1.21
  s21_decimal b = {{120, 0, 0, 2 << 16}};  // 1.20
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // 1.21 ≥ 1.20 => true
}
END_TEST

START_TEST(greater_or_equal_test_8_negative_numbers) {
  s21_decimal a = {{3, 0, 0, 0x80000000}};  // -3
  s21_decimal b = {{5, 0, 0, 0x80000000}};  // -5
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 1);  // -3 ≥ -5 => true
}
END_TEST

Suite *is_greater_or_equal_suite(void) {
  Suite *s = suite_create("GREATER_OR_EQUAL");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, greater_or_equal_test_1_basic_true);
  tcase_add_test(tc, greater_or_equal_test_2_equal_values);
  tcase_add_test(tc, greater_or_equal_test_3_less_false);
  tcase_add_test(tc, greater_or_equal_test_4_positive_vs_negative);
  tcase_add_test(tc, greater_or_equal_test_5_negative_vs_positive);
  tcase_add_test(tc, greater_or_equal_test_6_different_scales_equal);
  tcase_add_test(tc, greater_or_equal_test_7_different_scales_greater);
  tcase_add_test(tc, greater_or_equal_test_8_negative_numbers);

  suite_add_tcase(s, tc);
  return s;
}
