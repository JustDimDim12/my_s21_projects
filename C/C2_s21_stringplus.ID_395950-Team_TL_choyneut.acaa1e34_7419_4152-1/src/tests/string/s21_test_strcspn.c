#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_no_common_chars) {
  const char *str1 = "abcdef";
  const char *str2 = "xyz";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_first_char_matches) {
  const char *str1 = "hello";
  const char *str2 = "h";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_middle_char_matches) {
  const char *str1 = "abcdef";
  const char *str2 = "d";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_empty_str2) {
  const char *str1 = "abcdef";
  const char *str2 = "";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite *strcspn_suite(void) {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_no_common_chars);
  tcase_add_test(tc, test_first_char_matches);
  tcase_add_test(tc, test_middle_char_matches);
  tcase_add_test(tc, test_empty_str2);
  tcase_add_test(tc, test_empty_str1);

  suite_add_tcase(s, tc);
  return s;
}
