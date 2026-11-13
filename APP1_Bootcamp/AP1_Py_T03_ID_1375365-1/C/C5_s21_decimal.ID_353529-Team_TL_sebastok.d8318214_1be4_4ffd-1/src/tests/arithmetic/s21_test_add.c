#include <check.h>

#include "../../s21_decimal.h"

START_TEST(add_simple_positive) {
  s21_decimal a = {{5, 0, 0, 0}};  // 5
  s21_decimal b = {{7, 0, 0, 0}};  // 7
  s21_decimal res;

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 12);
  ck_assert_int_eq(s21_get_scale(&res), 0);
  ck_assert_int_eq(s21_get_sign(&res), 0);
}
END_TEST

START_TEST(add_with_scale) {
  s21_decimal a = {{12, 0, 0, 1 << 16}};   // 1.2
  s21_decimal b = {{123, 0, 0, 2 << 16}};  // 1.23
  s21_decimal res;

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 243);
  ck_assert_int_eq(s21_get_scale(&res), 2);
}
END_TEST

START_TEST(add_two_negative) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal b = {{3, 0, 0, 0x80000000}};  // -3
  s21_decimal res;

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 8);
  ck_assert_int_eq(s21_get_sign(&res), 1);
}
END_TEST

START_TEST(add_with_zero) {
  s21_decimal a = {{123, 0, 0, 0}};  // 123
  s21_decimal b = {{0, 0, 0, 0}};    // 0
  s21_decimal res;

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 123);
}
END_TEST

START_TEST(add_diff_signs_positive_result) {
  s21_decimal a = {{10, 0, 0, 0}};          // 10
  s21_decimal b = {{3, 0, 0, 0x80000000}};  // -3
  s21_decimal res;

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 7);
  ck_assert_int_eq(s21_get_sign(&res), 0);
}
END_TEST

START_TEST(add_diff_signs_negative_result) {
  s21_decimal a = {{10, 0, 0, 0x80000000}};  // -10
  s21_decimal b = {{3, 0, 0, 0}};            // 3
  s21_decimal res;

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 7);
  ck_assert_int_eq(s21_get_sign(&res), 1);
}
END_TEST

START_TEST(add_overflow) {
  s21_decimal huge = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal res;

  int code = s21_add(huge, one, &res);

  ck_assert_int_ne(code, 0);  // переполнение => ошибка
}
END_TEST

START_TEST(add_null_pointer) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  int code = s21_add(a, b, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *add_suite(void) {
  Suite *s = suite_create("ADD");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, add_simple_positive);
  tcase_add_test(tc, add_with_scale);
  tcase_add_test(tc, add_two_negative);
  tcase_add_test(tc, add_with_zero);
  tcase_add_test(tc, add_diff_signs_positive_result);
  tcase_add_test(tc, add_diff_signs_negative_result);
  tcase_add_test(tc, add_overflow);
  tcase_add_test(tc, add_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}
