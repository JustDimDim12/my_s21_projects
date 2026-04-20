#include <check.h>

#include "../../s21_decimal.h"

START_TEST(float_zero_error) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(0.0f, &dst);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(float_positive_integer) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(5.0f, &dst);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(dst.bits[0], 5);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(s21_get_scale(&dst), 0);
  ck_assert_int_eq(s21_get_sign(&dst), 0);
}
END_TEST

START_TEST(float_negative_integer) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(-5.0f, &dst);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(dst.bits[0], 5);
  ck_assert_int_eq(s21_get_scale(&dst), 0);
  ck_assert_int_eq(s21_get_sign(&dst), 1);
}
END_TEST

START_TEST(float_fractional_number) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(12.34f, &dst);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(dst.bits[0], 1234);
  ck_assert_int_eq(s21_get_scale(&dst), 2);
  ck_assert_int_eq(s21_get_sign(&dst), 0);
}
END_TEST

START_TEST(float_too_small) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(1e-30f, &dst);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(float_too_big) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(1e38f, &dst);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(float_nan) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(NAN, &dst);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(float_inf) {
  s21_decimal dst;
  int res = s21_from_float_to_decimal(INFINITY, &dst);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

Suite *from_float_suite(void) {
  Suite *s = suite_create("FROM_FLOAT");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, float_zero_error);
  tcase_add_test(tc, float_positive_integer);
  tcase_add_test(tc, float_negative_integer);
  tcase_add_test(tc, float_fractional_number);
  tcase_add_test(tc, float_too_small);
  tcase_add_test(tc, float_too_big);
  tcase_add_test(tc, float_nan);
  tcase_add_test(tc, float_inf);

  suite_add_tcase(s, tc);
  return s;
}
