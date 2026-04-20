#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_toupper_basic) {
  char str[] = "hello";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, "HELLO");
}
END_TEST

START_TEST(test_toupper_mixed) {
  char str[] = "HeLLo WoRLd";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, "HELLO WORLD");
}
END_TEST

START_TEST(test_toupper_no_lower) {
  char str[] = "ALREADY UPPER";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, "ALREADY UPPER");
}
END_TEST

START_TEST(test_toupper_empty) {
  char str[] = "";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, "");
}
END_TEST

START_TEST(test_toupper_null) {
  char *res = s21_to_upper(s21_NULL);
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

Suite *to_upper_suite(void) {
  Suite *s = suite_create("s21_to_upper");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_toupper_basic);
  tcase_add_test(tc, test_toupper_mixed);
  tcase_add_test(tc, test_toupper_no_lower);
  tcase_add_test(tc, test_toupper_empty);
  tcase_add_test(tc, test_toupper_null);

  suite_add_tcase(s, tc);

  return s;
}