#include <check.h>

#include "../../s21_decimal.h"

START_TEST(decimal_to_float_null_pointer) {
  s21_decimal src = {{1, 0, 0, 0}};
  int res = s21_from_decimal_to_float(src, NULL);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(decimal_to_float_positive_integer) {
  s21_decimal src = {{123, 0, 0, 0}};  // 123
  float dst;
  int res = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(res, OK);
  ck_assert_float_eq_tol(dst, 123.0f, 1e-6);
}
END_TEST

START_TEST(decimal_to_float_negative_integer) {
  s21_decimal src = {{123, 0, 0, 0x80000000}};  // -123
  float dst;
  int res = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(res, OK);
  ck_assert_float_eq_tol(dst, -123.0f, 1e-6);
}
END_TEST

START_TEST(decimal_to_float_with_scale) {
  s21_decimal src = {{12345, 0, 0, 2 << 16}};  // 123.45 (scale = 2)
  float dst;
  int res = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(res, OK);
  ck_assert_float_eq_tol(dst, 123.45f, 1e-6);
}
END_TEST

START_TEST(decimal_to_float_with_sign_and_scale) {
  s21_decimal src = {
      {505, 0, 0, (1 << 31) | (1 << 16)}};  // -50.5 (scale = 1, sign=1)
  float dst;
  int res = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(res, OK);
  ck_assert_float_eq_tol(dst, -50.5f, 1e-6);
}
END_TEST

START_TEST(decimal_to_float_scale_too_large) {
  s21_decimal src = {{1, 0, 0, 29 << 16}};  // scale = 29 → ERROR
  float dst;
  int res = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

Suite *from_decimal_to_float_suite(void) {
  Suite *s = suite_create("FROM_DECIMAL_TO_FLOAT");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, decimal_to_float_null_pointer);
  tcase_add_test(tc, decimal_to_float_positive_integer);
  tcase_add_test(tc, decimal_to_float_negative_integer);
  tcase_add_test(tc, decimal_to_float_with_scale);
  tcase_add_test(tc, decimal_to_float_with_sign_and_scale);
  tcase_add_test(tc, decimal_to_float_scale_too_large);

  suite_add_tcase(s, tc);
  return s;
}
