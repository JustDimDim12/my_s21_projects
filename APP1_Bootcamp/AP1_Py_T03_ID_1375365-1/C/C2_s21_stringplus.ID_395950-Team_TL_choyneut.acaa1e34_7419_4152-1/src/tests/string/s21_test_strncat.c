#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strncat_basic) {
  char my_dest[50] = "Hello, ";
  char sys_dest[50] = "Hello, ";
  char src[] = "world!";
  ck_assert_str_eq(s21_strncat(my_dest, src, 6), strncat(sys_dest, src, 6));
}
END_TEST

START_TEST(test_strncat_partial) {
  char my_dest[50] = "Hi ";
  char sys_dest[50] = "Hi ";
  char src[] = "there!";
  ck_assert_str_eq(s21_strncat(my_dest, src, 3), strncat(sys_dest, src, 3));
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char my_dest[50] = "Test";
  char sys_dest[50] = "Test";
  char src[] = "";
  ck_assert_str_eq(s21_strncat(my_dest, src, 5), strncat(sys_dest, src, 5));
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char my_dest[50] = "";
  char sys_dest[50] = "";
  char src[] = "abc";
  ck_assert_str_eq(s21_strncat(my_dest, src, 3), strncat(sys_dest, src, 3));
}
END_TEST

START_TEST(test_strncat_zero_n) {
  char my_dest[50] = "Keep";
  char sys_dest[50] = "Keep";
  char src[] = "going";
  ck_assert_str_eq(s21_strncat(my_dest, src, 0), strncat(sys_dest, src, 0));
}
END_TEST

Suite *strncat_suite(void) {
  Suite *s = suite_create("s21_strncat");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strncat_partial);
  tcase_add_test(tc, test_strncat_empty_src);
  tcase_add_test(tc, test_strncat_empty_dest);
  tcase_add_test(tc, test_strncat_zero_n);

  suite_add_tcase(s, tc);
  return s;
}
