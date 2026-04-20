#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strstr_middle) {
  char haystack[] = "The quick brown fox";
  char needle[] = "quick";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_start) {
  char haystack[] = "hello world";
  char needle[] = "hello";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_end) {
  char haystack[] = "abcdef";
  char needle[] = "def";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_none) {
  char haystack[] = "abcdef";
  char needle[] = "xyz";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  char haystack[] = "abcdef";
  char needle[] = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *strstr_suite(void) {
  Suite *s = suite_create("s21_strstr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strstr_middle);
  tcase_add_test(tc, test_strstr_start);
  tcase_add_test(tc, test_strstr_end);
  tcase_add_test(tc, test_strstr_none);
  tcase_add_test(tc, test_strstr_empty_needle);

  suite_add_tcase(s, tc);
  return s;
}
