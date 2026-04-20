#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_memcmp_equal) {
  char str1[] = "abcdef";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(test_memcmp_diff_start) {
  char str1[] = "xbcdef";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(test_memcmp_diff_middle) {
  char str1[] = "abXdef";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(test_memcmp_diff_end) {
  char str1[] = "abcdeX";
  char str2[] = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(test_memcmp_zero_n) {
  char str1[] = "abcdef";
  char str2[] = "ghijkl";
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

Suite *memcmp_suite(void) {
  Suite *s = suite_create("memcmp");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_memcmp_equal);
  tcase_add_test(tc, test_memcmp_diff_start);
  tcase_add_test(tc, test_memcmp_diff_middle);
  tcase_add_test(tc, test_memcmp_diff_end);
  tcase_add_test(tc, test_memcmp_zero_n);

  suite_add_tcase(s, tc);
  return s;
}
