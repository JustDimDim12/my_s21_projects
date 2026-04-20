#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strtok_commas) {
  char str1[] = "apple,banana,orange";
  char str2[] = "apple,banana,orange";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  while (token1 != s21_NULL && token2 != s21_NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(s21_NULL, ",");
    token2 = strtok(s21_NULL, ",");
  }
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_multiple_delims) {
  char str1[] = "apple,,banana,,,orange";
  char str2[] = "apple,,banana,,,orange";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  while (token1 != s21_NULL && token2 != s21_NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(s21_NULL, ",");
    token2 = strtok(s21_NULL, ",");
  }
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_spaces) {
  char str1[] = "   red   green blue ";
  char str2[] = "   red   green blue ";
  char *token1 = s21_strtok(str1, " ");
  char *token2 = strtok(str2, " ");
  while (token1 != s21_NULL && token2 != s21_NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(s21_NULL, " ");
    token2 = strtok(s21_NULL, " ");
  }
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_start) {
  char str1[] = "one two three";
  char str2[] = "one two three";
  ck_assert_str_eq(s21_strtok(str1, " "), strtok(str2, " "));
}
END_TEST

START_TEST(test_strtok_end_delims) {
  char str1[] = "hello world ";
  char str2[] = "hello world ";
  char *token1 = s21_strtok(str1, " ");
  char *token2 = strtok(str2, " ");
  while (token1 != s21_NULL && token2 != s21_NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(s21_NULL, " ");
    token2 = strtok(s21_NULL, " ");
  }
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_only_delims) {
  char str1[] = ",,,";
  char str2[] = ",,,";
  ck_assert_ptr_eq(s21_strtok(str1, ","), strtok(str2, ","));
}
END_TEST

START_TEST(test_strtok_empty_string) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_ptr_eq(s21_strtok(str1, ","), strtok(str2, ","));
}
END_TEST

START_TEST(test_strtok_no_delims) {
  char str1[] = "apple";
  char str2[] = "apple";
  ck_assert_str_eq(s21_strtok(str1, ","), strtok(str2, ","));
  ck_assert_ptr_eq(s21_strtok(s21_NULL, ","), strtok(s21_NULL, ","));
}
END_TEST

Suite *strtok_suite(void) {
  Suite *s = suite_create("s21_strtok");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strtok_commas);
  tcase_add_test(tc, test_strtok_multiple_delims);
  tcase_add_test(tc, test_strtok_spaces);
  tcase_add_test(tc, test_strtok_start);
  tcase_add_test(tc, test_strtok_end_delims);
  tcase_add_test(tc, test_strtok_only_delims);
  tcase_add_test(tc, test_strtok_empty_string);
  tcase_add_test(tc, test_strtok_no_delims);

  suite_add_tcase(s, tc);
  return s;
}
