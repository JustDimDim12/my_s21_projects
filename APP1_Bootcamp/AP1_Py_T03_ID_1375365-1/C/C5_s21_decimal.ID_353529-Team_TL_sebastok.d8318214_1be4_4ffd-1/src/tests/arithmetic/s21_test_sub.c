#include <check.h>

#include "../../s21_decimal.h"

START_TEST(sub_simple_positive) {
  // 10 - 3 = 7
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 7);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(sub_with_scale) {
  // 5.5 - 2.2 = 3.3
  s21_decimal a = {{55, 0, 0, 1 << 16}};  // scale = 1
  s21_decimal b = {{22, 0, 0, 1 << 16}};

  s21_decimal result;
  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 33);
  ck_assert_int_eq(s21_get_scale(&result), 1);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(sub_two_negative) {
  // (-10) - (-3) = -7
  s21_decimal a = {{10, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};

  s21_decimal result;
  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 7);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(sub_with_zero) {
  // 123 - 0 = 123
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 123);
}
END_TEST

START_TEST(sub_diff_signs_positive_result) {
  // 5 - (-3) = 8
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(sub_diff_signs_negative_result) {
  // (-5) - (3) = -8
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(sub_overflow) {
  // Large minus (-1), expecting overflow
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};

  s21_decimal result;
  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, 1);  // overflow normalization error
}
END_TEST

START_TEST(sub_null_pointer) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};

  int code = s21_sub(a, b, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *sub_suite(void) {
  Suite *s = suite_create("SUB");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sub_simple_positive);
  tcase_add_test(tc, sub_with_scale);
  tcase_add_test(tc, sub_two_negative);
  tcase_add_test(tc, sub_with_zero);
  tcase_add_test(tc, sub_diff_signs_positive_result);
  tcase_add_test(tc, sub_diff_signs_negative_result);
  tcase_add_test(tc, sub_overflow);
  tcase_add_test(tc, sub_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}
