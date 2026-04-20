#include <check.h>

#include "../../s21_decimal.h"

START_TEST(div_simple) {
  s21_decimal a = {{10, 0, 0, 0}};  // 10
  s21_decimal b = {{2, 0, 0, 0}};   // 2
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, b, &res), 0);

  s21_decimal expected = {{5, 0, 0, 0}};  // 5
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(div_with_scale) {
  s21_decimal a = {{123, 0, 0, 2 << 16}};  // 1.23
  s21_decimal b = {{2, 0, 0, 0}};          // 2
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, b, &res), 0);

  s21_decimal expected = {{615, 0, 0, 3 << 16}};  // 0.615
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(div_by_zero) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, b, &res), 3);  // деление на 0
}
END_TEST

START_TEST(div_zero_by_any) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, b, &res), 0);

  s21_decimal expected = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(div_negative) {
  s21_decimal a = {{10, 0, 0, 0}};        // 10
  s21_decimal b = {{2, 0, 0, 1u << 31}};  // -2
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, b, &res), 0);

  s21_decimal expected = {{5, 0, 0, 1u << 31}};  // -5
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(div_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  int code = s21_div(a, b, &res);
  ck_assert_int_eq(code, 1);
}
END_TEST

// Деление числа на само себя = 1
START_TEST(div_self) {
  s21_decimal a = {{12345, 0, 0, 0}};
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, a, &res), 0);

  s21_decimal expected = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

// Деление чисел с большим scale
START_TEST(div_large_scale) {
  s21_decimal a = {{123456789, 0, 0, 6 << 16}};  // 123.456789
  s21_decimal b = {{10000, 0, 0, 4 << 16}};      // 1.0000
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, b, &res), 0);

  s21_decimal expected = {
      {123456789, 0, 0, 6 << 16}};  // результат = 123.456789
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

// Деление двух отрицательных чисел = положительный результат
START_TEST(div_two_negative) {
  s21_decimal a = {{50, 0, 0, 1u << 31}};  // -50
  s21_decimal b = {{2, 0, 0, 1u << 31}};   // -2
  s21_decimal res;

  ck_assert_int_eq(s21_div(a, b, &res), 0);

  s21_decimal expected = {{25, 0, 0, 0}};  // 25
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

// ------------------------ SUITE -------------------------

Suite *suite_s21_div() {
  Suite *s = suite_create("s21_div");
  TCase *tc_div = tcase_create("div");

  tcase_add_test(tc_div, div_simple);
  tcase_add_test(tc_div, div_with_scale);
  tcase_add_test(tc_div, div_by_zero);
  tcase_add_test(tc_div, div_zero_by_any);
  tcase_add_test(tc_div, div_negative);
  tcase_add_test(tc_div, div_overflow);
  tcase_add_test(tc_div, div_self);
  tcase_add_test(tc_div, div_large_scale);
  tcase_add_test(tc_div, div_two_negative);

  suite_add_tcase(s, tc_div);

  return s;
}
