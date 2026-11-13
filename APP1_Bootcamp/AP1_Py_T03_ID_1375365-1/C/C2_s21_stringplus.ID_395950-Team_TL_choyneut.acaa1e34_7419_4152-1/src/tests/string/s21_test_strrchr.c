#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strrchr_multiple) {
  char str[] = "banana";
  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
}
END_TEST

START_TEST(test_strrchr_single) {
  char str[] = "apple";
  ck_assert_ptr_eq(s21_strrchr(str, 'p'), strrchr(str, 'p'));
}
END_TEST

START_TEST(test_strrchr_none) {
  char str[] = "orange";
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_strrchr_null_char) {
  char str[] = "melon";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_strrchr_empty) {
  char str[] = "";
  ck_assert_ptr_eq(s21_strrchr(str, 'x'), strrchr(str, 'x'));
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

Suite *strrchr_suite(void) {
  Suite *s = suite_create("s21_strrchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strrchr_multiple);
  tcase_add_test(tc, test_strrchr_single);
  tcase_add_test(tc, test_strrchr_none);
  tcase_add_test(tc, test_strrchr_null_char);
  tcase_add_test(tc, test_strrchr_empty);

  suite_add_tcase(s, tc);
  return s;
}
