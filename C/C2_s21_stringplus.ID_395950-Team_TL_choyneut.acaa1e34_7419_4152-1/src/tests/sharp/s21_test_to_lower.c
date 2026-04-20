#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../../s21_string.h"

// Базовый случай — обычные заглавные буквы
START_TEST(test_tolower_basic) {
  char str[] = "HELLO";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, "hello");
}
END_TEST

START_TEST(test_tolower_mixed) {
  char str[] = "HeLLo WoRLd";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, "hello world");
}
END_TEST

START_TEST(test_tolower_no_caps) {
  char str[] = "already lower";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, "already lower");
}
END_TEST

START_TEST(test_tolower_empty) {
  char str[] = "";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, "");
}
END_TEST

START_TEST(test_tolower_null) {
  char *res = s21_to_lower(s21_NULL);
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

Suite *to_lower_suite(void) {
  Suite *s = suite_create("s21_to_lower");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_tolower_basic);
  tcase_add_test(tc, test_tolower_mixed);
  tcase_add_test(tc, test_tolower_no_caps);
  tcase_add_test(tc, test_tolower_empty);
  tcase_add_test(tc, test_tolower_null);

  suite_add_tcase(s, tc);
  return s;
}
