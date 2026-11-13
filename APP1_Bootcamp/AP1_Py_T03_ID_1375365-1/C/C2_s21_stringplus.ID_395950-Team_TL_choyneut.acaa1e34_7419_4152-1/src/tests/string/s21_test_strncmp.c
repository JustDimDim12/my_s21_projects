#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strncmp_equal) {
  char str1[] = "abcdef";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_diff_start) {
  char str1[] = "xbcdef";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_diff_middle) {
  char str1[] = "abXdef";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_n_limit) {
  char str1[] = "abcdef";
  char str2[] = "abcxyz";
  ck_assert_int_eq(s21_strncmp(str1, str2, 3), strncmp(str1, str2, 3));
}
END_TEST

START_TEST(test_strncmp_short_string) {
  char str1[] = "abc";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

Suite *strncmp_suite(void) {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncmp_equal);
  tcase_add_test(tc, test_strncmp_diff_start);
  tcase_add_test(tc, test_strncmp_diff_middle);
  tcase_add_test(tc, test_strncmp_n_limit);
  tcase_add_test(tc, test_strncmp_short_string);

  suite_add_tcase(s, tc);
  return s;
}
