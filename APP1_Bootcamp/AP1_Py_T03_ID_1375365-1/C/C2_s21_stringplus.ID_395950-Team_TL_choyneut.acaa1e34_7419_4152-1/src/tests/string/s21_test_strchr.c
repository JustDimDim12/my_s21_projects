#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strchr_start) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_strchr(str, 's'), strchr(str, 's'));
}
END_TEST

START_TEST(test_strchr_middle) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_strchr(str, 'h'), strchr(str, 'h'));
}
END_TEST

START_TEST(test_strchr_end) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_strchr(str, '1'), strchr(str, '1'));
}
END_TEST

START_TEST(test_strchr_not_found) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_strchr(str, 'x'), strchr(str, 'x'));
}
END_TEST

START_TEST(test_strchr_null_terminator) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

Suite *strchr_suite(void) {
  Suite *s = suite_create("strchr");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_strchr_start);
  tcase_add_test(tc, test_strchr_middle);
  tcase_add_test(tc, test_strchr_end);
  tcase_add_test(tc, test_strchr_not_found);
  tcase_add_test(tc, test_strchr_null_terminator);

  suite_add_tcase(s, tc);
  return s;
}
