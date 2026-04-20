#include <check.h>

#include "../../s21_decimal.h"

START_TEST(less_test_1_basic_positive) {
  s21_decimal a = {{3, 0, 0, 0}};  // 3
  s21_decimal b = {{5, 0, 0, 0}};  // 5
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 1);  // 3 < 5
}
END_TEST

START_TEST(less_test_2_basic_negative) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal b = {{3, 0, 0, 0x80000000}};  // -3
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 1);  // -5 < -3
}
END_TEST

START_TEST(less_test_3_negative_vs_positive) {
  s21_decimal a = {{2, 0, 0, 0x80000000}};  // -2
  s21_decimal b = {{2, 0, 0, 0}};           // 2
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 1);  // -2 < 2
}
END_TEST

START_TEST(less_test_4_positive_vs_negative) {
  s21_decimal a = {{2, 0, 0, 0}};           // 2
  s21_decimal b = {{2, 0, 0, 0x80000000}};  // -2
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 0);  // 2 < -2 => false
}
END_TEST

START_TEST(less_test_5_equal_values_different_scales) {
  s21_decimal a = {{1, 0, 0, 0}};         // 1
  s21_decimal b = {{10, 0, 0, 1 << 16}};  // 1.0
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 0);  // 1 == 1.0 => false
}
END_TEST

START_TEST(less_test_6_less_values_different_scales) {
  s21_decimal a = {{120, 0, 0, 2 << 16}};  // 1.20
  s21_decimal b = {{121, 0, 0, 2 << 16}};  // 1.21
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 1);  // 1.20 < 1.21
}
END_TEST

START_TEST(less_test_7_negative_less_than_positive_zero) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};  // -0
  s21_decimal b = {{0, 0, 0, 0}};           // +0
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 0);  // -0 < +0 => false
}
END_TEST

START_TEST(less_test_8_big_numbers) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0, 0, 0, 0}};  // 0
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 0);  // большое число не меньше 0
}
END_TEST

START_TEST(less_test_9_negative_different_scales) {
  s21_decimal a = {{1200, 0, 0, (2 << 16) | 0x80000000}};  // -12.00
  s21_decimal b = {{1199, 0, 0, (2 << 16) | 0x80000000}};  // -11.99
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 1);  // -12.00 < -11.99
}
END_TEST

START_TEST(less_test_10_equal_negatives) {
  s21_decimal a = {{100, 0, 0, (2 << 16) | 0x80000000}};  // -1.00
  s21_decimal b = {{10, 0, 0, (1 << 16) | 0x80000000}};   // -1.0
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 0);  // -1.00 == -1.0 => false
}
END_TEST

Suite *is_less_suite(void) {
  Suite *s = suite_create("LESS");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, less_test_1_basic_positive);
  tcase_add_test(tc, less_test_2_basic_negative);
  tcase_add_test(tc, less_test_3_negative_vs_positive);
  tcase_add_test(tc, less_test_4_positive_vs_negative);
  tcase_add_test(tc, less_test_5_equal_values_different_scales);
  tcase_add_test(tc, less_test_6_less_values_different_scales);
  tcase_add_test(tc, less_test_7_negative_less_than_positive_zero);
  tcase_add_test(tc, less_test_8_big_numbers);
  tcase_add_test(tc, less_test_9_negative_different_scales);
  tcase_add_test(tc, less_test_10_equal_negatives);

  suite_add_tcase(s, tc);
  return s;
}
