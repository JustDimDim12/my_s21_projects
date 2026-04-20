#include <check.h>

#include "../../s21_decimal.h"

START_TEST(equal_test_1) {
  s21_decimal number1 = {{1 << 3, 1 << 3, 1 << 3, 0}};
  s21_decimal number2 = {{1 << 3, 1 << 3, 1 << 3, 0}};
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(equal_test_2_different_signs) {
  s21_decimal number1 = {{123, 0, 0, 0}};
  s21_decimal number2 = {{123, 0, 0, 0x80000000}};
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(equal_test_3_positive_negative_zero) {
  s21_decimal number1 = {{0, 0, 0, 0}};
  s21_decimal number2 = {{0, 0, 0, 0x80000000}};
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(equal_test_4_different_scales_equal_values) {
  s21_decimal number1 = {{1, 0, 0, 0}};         // 1
  s21_decimal number2 = {{10, 0, 0, 1 << 16}};  // 1.0
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 1);  // 1 == 1.0
}
END_TEST

START_TEST(equal_test_5_different_scales_not_equal) {
  s21_decimal number1 = {{123, 0, 0, 1 << 16}};  // 1.23
  s21_decimal number2 = {{124, 0, 0, 1 << 16}};  // 1.24
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 0);  // 1.23 != 1.24
}
END_TEST

START_TEST(equal_test_6_big_numbers_equal) {
  s21_decimal number1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal number2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 1);  // большие числа равны
}
END_TEST

START_TEST(equal_test_7_zero_different_scales) {
  s21_decimal number1 = {{0, 0, 0, 0}};        // 0
  s21_decimal number2 = {{0, 0, 0, 5 << 16}};  // 0.00000
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 1);  // 0 == 0.00000
}
END_TEST

START_TEST(equal_test_8_same_value_different_signs_and_scales) {
  s21_decimal number1 = {{1230, 0, 0, 1 << 16}};                  // 12.30
  s21_decimal number2 = {{12300, 0, 0, (2 << 16) | 0x80000000}};  // -12.300
  int res = s21_is_equal(number1, number2);
  ck_assert_int_eq(res, 0);  // +12.30 != -12.300
}
END_TEST

Suite *is_equal_suite(void) {
  Suite *s = suite_create("EQUAL");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, equal_test_1);
  tcase_add_test(tc, equal_test_2_different_signs);
  tcase_add_test(tc, equal_test_3_positive_negative_zero);
  tcase_add_test(tc, equal_test_4_different_scales_equal_values);
  tcase_add_test(tc, equal_test_5_different_scales_not_equal);
  tcase_add_test(tc, equal_test_6_big_numbers_equal);
  tcase_add_test(tc, equal_test_7_zero_different_scales);
  tcase_add_test(tc, equal_test_8_same_value_different_signs_and_scales);

  suite_add_tcase(s, tc);
  return s;
}