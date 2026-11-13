#include <check.h>

#include "../../s21_decimal.h"

START_TEST(from_int_null_pointer) {
  int res = s21_from_int_to_decimal(5, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_int_zero) {
  s21_decimal dst;
  s21_from_int_to_decimal(0, &dst);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);  // ни знака, ни масштаба
}
END_TEST

START_TEST(from_int_positive) {
  s21_decimal dst;
  s21_from_int_to_decimal(123, &dst);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(from_int_negative) {
  s21_decimal dst;
  s21_from_int_to_decimal(-123, &dst);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0x80000000);  // знак установлен, scale = 0
}
END_TEST

START_TEST(from_int_max_int) {
  s21_decimal dst;
  s21_from_int_to_decimal(2147483647, &dst);
  ck_assert_int_eq(dst.bits[0], 2147483647);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(from_int_min_int) {
  s21_decimal dst;
  s21_from_int_to_decimal(-2147483648, &dst);
  ck_assert_int_eq(dst.bits[0], 2147483648u);  // модуль числа
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0x80000000);  // только знак
}
END_TEST

Suite *from_int_suite(void) {
  Suite *s = suite_create("FROM_INT");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, from_int_null_pointer);
  tcase_add_test(tc, from_int_zero);
  tcase_add_test(tc, from_int_positive);
  tcase_add_test(tc, from_int_negative);
  tcase_add_test(tc, from_int_max_int);
  tcase_add_test(tc, from_int_min_int);

  suite_add_tcase(s, tc);
  return s;
}
