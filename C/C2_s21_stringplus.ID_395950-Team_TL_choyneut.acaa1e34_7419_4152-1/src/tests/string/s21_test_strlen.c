#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strlen_empty) {
  char str[] = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_normal) {
  char str[] = "Hello";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_spaces) {
  char str[] = "  Hello world  ";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_with_null_inside) {
  char str[] = {'a', 'b', '\0', 'c', 'd', '\0'};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_long) {
  char str[1001];
  memset(str, 'x', 1000);
  str[1000] = '\0';
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *strlen_suite(void) {
  Suite *s = suite_create("s21_strlen");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_normal);
  tcase_add_test(tc, test_strlen_spaces);
  tcase_add_test(tc, test_strlen_with_null_inside);
  tcase_add_test(tc, test_strlen_long);

  suite_add_tcase(s, tc);
  return s;
}
