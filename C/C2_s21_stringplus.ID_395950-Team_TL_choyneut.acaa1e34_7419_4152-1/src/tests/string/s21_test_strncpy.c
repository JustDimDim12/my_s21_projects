#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strncpy_basic) {
  char dest1[20] = "XXXXXXXXXX";
  char dest2[20] = "XXXXXXXXXX";
  const char *src = "Hello, world!";
  ck_assert_str_eq(s21_strncpy(dest1, src, 5), strncpy(dest2, src, 5));
}
END_TEST

START_TEST(test_strncpy_short_src) {
  char dest1[10] = "abcdefghi";
  char dest2[10] = "abcdefghi";
  const char *src = "Hi";
  ck_assert_str_eq(s21_strncpy(dest1, src, 5), strncpy(dest2, src, 5));
}
END_TEST

START_TEST(test_strncpy_empty_src) {
  char dest1[10] = "123456789";
  char dest2[10] = "123456789";
  const char *src = "";
  ck_assert_str_eq(s21_strncpy(dest1, src, 5), strncpy(dest2, src, 5));
}
END_TEST

START_TEST(test_strncpy_exact_n) {
  char dest1[20] = "";
  char dest2[20] = "";
  const char *src = "abcdef";
  ck_assert_str_eq(s21_strncpy(dest1, src, 6), strncpy(dest2, src, 6));
}
END_TEST

START_TEST(test_strncpy_n_longer_than_src) {
  char dest1[20] = "AAAAAAAAAAAAAAAAA";
  char dest2[20] = "AAAAAAAAAAAAAAAAA";
  const char *src = "cat";
  ck_assert_str_eq(s21_strncpy(dest1, src, 10), strncpy(dest2, src, 10));
}
END_TEST

Suite *strncpy_suite(void) {
  Suite *s = suite_create("s21_strncpy");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncpy_basic);
  tcase_add_test(tc, test_strncpy_short_src);
  tcase_add_test(tc, test_strncpy_empty_src);
  tcase_add_test(tc, test_strncpy_exact_n);
  tcase_add_test(tc, test_strncpy_n_longer_than_src);

  suite_add_tcase(s, tc);
  return s;
}
