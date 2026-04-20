#include <check.h>

#include "../../s21_decimal.h"

START_TEST(test_negate_positive) {
  s21_decimal value = {{123, 0, 0, 0}};  // 123
  s21_decimal result;

  int status = s21_negate(value, &result);

  ck_assert_int_eq(status, 0);  // Ожидаем 0
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal value = {{123, 0, 0, 0}};
  s21_set_sign(&value, 1);  // -123
  s21_decimal result;

  int status = s21_negate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};  // 0
  s21_decimal result;

  int status = s21_negate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(&result), 1);  // теперь -0
}
END_TEST

START_TEST(test_negate_negative_zero_back) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_sign(&value, 1);  // -0
  s21_decimal result;

  int status = s21_negate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(&result), 0);  // теперь +0
}
END_TEST

Suite *test_negate(void) {
  Suite *s = suite_create("NEGATE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_negate_positive);
  tcase_add_test(tc, test_negate_negative);
  tcase_add_test(tc, test_negate_zero);
  tcase_add_test(tc, test_negate_negative_zero_back);

  suite_add_tcase(s, tc);
  return s;
}
