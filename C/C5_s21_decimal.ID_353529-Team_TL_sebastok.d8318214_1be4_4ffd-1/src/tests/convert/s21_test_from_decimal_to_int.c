#include <check.h>

#include "../../s21_decimal.h"

START_TEST(test_decimal_to_int_positive) {
  s21_decimal dec = {{123, 0, 0, 0}};  // scale = 0, sign = 0
  int result = 0;

  int status = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(status, CONVERSION_SUCCESS);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_decimal_to_int_negative) {
  s21_decimal dec = {{123, 0, 0, 0}};
  s21_set_sign(&dec, 1);  // отрицательный
  int result = 0;

  int status = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(status, CONVERSION_SUCCESS);
  ck_assert_int_eq(result, -123);
}
END_TEST

START_TEST(test_decimal_to_int_with_scale) {
  s21_decimal dec = {{12345, 0, 0, 0}};
  s21_set_scale(&dec, 2);  // 123.45
  int result = 0;

  int status = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(status, CONVERSION_SUCCESS);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_decimal_to_int_round_down) {
  s21_decimal dec = {{199, 0, 0, 0}};
  s21_set_scale(&dec, 2);  // 1.99
  int result = 0;

  int status = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(status, CONVERSION_SUCCESS);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_to_int_overflow_positive) {
  s21_decimal dec = {{0, 0, 0, 0}};
  dec.bits[0] = INT_MAX;
  dec.bits[1] = 1;  // увеличиваем значение явно выше INT_MAX
  int result = 0;

  int status = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(status, CONVERSION_OVERFLOW);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_to_int_overflow_negative) {
  s21_decimal dec = {{0, 0, 0, 0}};
  dec.bits[0] = INT_MAX;
  dec.bits[1] = 1;
  s21_set_sign(&dec, 1);
  int result = 0;

  int status = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(status, CONVERSION_OVERFLOW);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_to_int_null_pointer) {
  s21_decimal dec = {{123, 0, 0, 0}};
  int status = s21_from_decimal_to_int(dec, NULL);

  ck_assert_int_eq(status, CONVERT_ERROR);
}
END_TEST

Suite *test_convert_decimal_to_int(void) {
  Suite *s = suite_create("FROM_DECIMAL_TO_INT");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_decimal_to_int_positive);
  tcase_add_test(tc, test_decimal_to_int_negative);
  tcase_add_test(tc, test_decimal_to_int_with_scale);
  tcase_add_test(tc, test_decimal_to_int_round_down);
  tcase_add_test(tc, test_decimal_to_int_overflow_positive);
  tcase_add_test(tc, test_decimal_to_int_overflow_negative);
  tcase_add_test(tc, test_decimal_to_int_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}
