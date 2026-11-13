#include <check.h>

#include "../../s21_decimal.h"

START_TEST(not_equal_test_1_equal_values) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 0);  // 10 == 10 => not equal = false
}
END_TEST

START_TEST(not_equal_test_2_different_values) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{6, 0, 0, 0}};
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 1);  // 5 != 6 => true
}
END_TEST

START_TEST(not_equal_test_3_different_signs) {
  s21_decimal a = {{123, 0, 0, 0}};           // +123
  s21_decimal b = {{123, 0, 0, 0x80000000}};  // -123
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 1);  // +123 != -123
}
END_TEST

START_TEST(not_equal_test_4_zero_and_negative_zero) {
  s21_decimal a = {{0, 0, 0, 0}};           // +0
  s21_decimal b = {{0, 0, 0, 0x80000000}};  // -0
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 0);  // +0 == -0 => not equal = false
}
END_TEST

START_TEST(not_equal_test_5_equal_with_different_scale) {
  s21_decimal a = {{1, 0, 0, 0}};         // 1
  s21_decimal b = {{10, 0, 0, 1 << 16}};  // 1.0
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 0);  // 1 == 1.0 => not equal = false
}
END_TEST

START_TEST(not_equal_test_6_not_equal_with_different_scale) {
  s21_decimal a = {{120, 0, 0, 2 << 16}};  // 1.20
  s21_decimal b = {{121, 0, 0, 2 << 16}};  // 1.21
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 1);  // 1.20 != 1.21 => true
}
END_TEST

START_TEST(not_equal_test_7_big_numbers_equal) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 0);  // большие равны => false
}
END_TEST

Suite *is_not_equal_suite(void) {
  Suite *s = suite_create("NOT_EQUAL");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, not_equal_test_1_equal_values);
  tcase_add_test(tc, not_equal_test_2_different_values);
  tcase_add_test(tc, not_equal_test_3_different_signs);
  tcase_add_test(tc, not_equal_test_4_zero_and_negative_zero);
  tcase_add_test(tc, not_equal_test_5_equal_with_different_scale);
  tcase_add_test(tc, not_equal_test_6_not_equal_with_different_scale);
  tcase_add_test(tc, not_equal_test_7_big_numbers_equal);

  suite_add_tcase(s, tc);
  return s;
}
