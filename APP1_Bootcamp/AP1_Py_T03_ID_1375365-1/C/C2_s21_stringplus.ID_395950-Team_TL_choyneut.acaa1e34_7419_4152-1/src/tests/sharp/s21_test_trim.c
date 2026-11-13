#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_trim_basic) {
  const char *src = "   hello world   ";
  char *res = s21_trim(src, " ");
  ck_assert_str_eq(res, "hello world");
  free(res);
}
END_TEST

START_TEST(test_trim_custom_chars) {
  const char *src = ",,,..hello..,,";
  char *res = s21_trim(src, ",.");
  ck_assert_str_eq(res, "hello");
  free(res);
}
END_TEST

START_TEST(test_trim_default_chars) {
  const char *src = "\t\n  hi there \n\t";
  char *res = s21_trim(src, s21_NULL);
  ck_assert_str_eq(res, "hi there");
  free(res);
}
END_TEST

START_TEST(test_trim_no_trim_needed) {
  const char *src = "clean";
  char *res = s21_trim(src, " ");
  ck_assert_str_eq(res, "clean");
  free(res);
}
END_TEST

START_TEST(test_trim_null_input) {
  char *res = s21_trim(s21_NULL, " ");
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

Suite *trim_suite(void) {
  Suite *s = suite_create("s21_trim");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_trim_basic);
  tcase_add_test(tc, test_trim_custom_chars);
  tcase_add_test(tc, test_trim_default_chars);
  tcase_add_test(tc, test_trim_no_trim_needed);
  tcase_add_test(tc, test_trim_null_input);

  suite_add_tcase(s, tc);
  return s;
}
