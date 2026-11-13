#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strpbk_middle) {
  char str1[] = "abcdef";
  char str2[] = "dx";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbk_start) {
  char str1[] = "abcdef";
  char str2[] = "a123";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbk_end) {
  char str1[] = "abcdef";
  char str2[] = "fz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbk_none) {
  char str1[] = "abcdef";
  char str2[] = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbk_empty_str1) {
  char str1[] = "";
  char str2[] = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *strpbrk_suite(void) {
  Suite *s = suite_create("s21_strpbrk");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strpbk_middle);
  tcase_add_test(tc, test_strpbk_start);
  tcase_add_test(tc, test_strpbk_end);
  tcase_add_test(tc, test_strpbk_none);
  tcase_add_test(tc, test_strpbk_empty_str1);

  suite_add_tcase(s, tc);
  return s;
}
