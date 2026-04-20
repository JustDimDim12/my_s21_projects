#include <check.h>

#include "../../s21_decimal.h"

START_TEST(floor_positive_no_scale) {
  s21_decimal value = {{123, 0, 0, 0}};  // 123
  s21_decimal result;

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(s21_get_sign(&result), 0);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(floor_positive_fraction) {
  s21_decimal value = {{12345, 0, 0, 0}};  // 123.45
  s21_set_scale(&value, 2);
  s21_decimal result;

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(s21_get_sign(&result), 0);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(floor_negative_fraction) {
  s21_decimal value = {{12345, 0, 0, 0}};  // -123.45
  s21_set_scale(&value, 2);
  s21_set_sign(&value, 1);
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 124);  // -123.45 -> -124
  ck_assert_int_eq(s21_get_sign(&result), 1);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(floor_negative_already_integer) {
  s21_decimal value = {{123, 0, 0, 0}};  // -123
  s21_set_sign(&value, 1);
  s21_decimal result;

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(s21_get_sign(&result), 1);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(floor_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(&result), 0);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(floor_invalid_scale) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_set_scale(&value, 32);  // scale слишком большой
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 1);  // функция должна вернуть флаг ошибки
}
END_TEST

Suite *test_floor(void) {
  Suite *s = suite_create("FLOOR");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, floor_positive_no_scale);
  tcase_add_test(tc, floor_positive_fraction);
  tcase_add_test(tc, floor_negative_fraction);
  tcase_add_test(tc, floor_negative_already_integer);
  tcase_add_test(tc, floor_zero);
  tcase_add_test(tc, floor_invalid_scale);

  suite_add_tcase(s, tc);
  return s;
}
