#include <check.h>

#include "../../s21_decimal.h"

START_TEST(test_truncate_no_fraction) {
  s21_decimal value = {{123, 0, 0, 0}};  // 123
  s21_decimal result;

  int status = s21_truncate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(s21_get_scale(&result), 0);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(test_truncate_fraction_low) {
  s21_decimal value = {{1234, 0, 0, 0}};  // 12.34
  s21_set_scale(&value, 2);
  s21_decimal result;

  int status = s21_truncate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 12);  // 12.34 → 12
  ck_assert_int_eq(s21_get_scale(&result), 0);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(test_truncate_fraction_high) {
  s21_decimal value = {{1299, 0, 0, 0}};  // 12.99
  s21_set_scale(&value, 2);
  s21_decimal result;

  int status = s21_truncate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 12);  // 12.99 → 12 (не 13!)
  ck_assert_int_eq(s21_get_scale(&result), 0);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(test_truncate_negative_low) {
  s21_decimal value = {{1234, 0, 0, 0}};  // -12.34
  s21_set_scale(&value, 2);
  s21_set_sign(&value, 1);
  s21_decimal result;

  int status = s21_truncate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 12);  // -12.34 → -12
  ck_assert_int_eq(s21_get_scale(&result), 0);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_truncate_negative_high) {
  s21_decimal value = {{1299, 0, 0, 0}};  // -12.99
  s21_set_scale(&value, 2);
  s21_set_sign(&value, 1);
  s21_decimal result;

  int status = s21_truncate(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 12);  // -12.99 → -12 (не -13!)
  ck_assert_int_eq(s21_get_scale(&result), 0);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

Suite *test_truncate(void) {
  Suite *s = suite_create("TRUNCATE");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_truncate_no_fraction);
  tcase_add_test(tc, test_truncate_fraction_low);
  tcase_add_test(tc, test_truncate_fraction_high);
  tcase_add_test(tc, test_truncate_negative_low);
  tcase_add_test(tc, test_truncate_negative_high);

  suite_add_tcase(s, tc);
  return s;
}