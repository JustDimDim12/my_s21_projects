#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_memchr_1) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_memchr(str, 's', 9), memchr(str, 's', 9));
}
END_TEST

START_TEST(test_memchr_2) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_memchr(str, '1', 9), memchr(str, '1', 9));
}
END_TEST

START_TEST(test_memchr_3) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_memchr(str, '3', 9), memchr(str, '3', 9));
}
END_TEST

START_TEST(test_memchr_4) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_memchr(str, 'o', 9), memchr(str, 'o', 9));
}
END_TEST

START_TEST(test_memchr_5) {
  char str[] = "school21";
  ck_assert_ptr_eq(s21_memchr(str, '1', 5), memchr(str, '1', 5));
}
END_TEST

Suite *memchr_suite(void) {
  Suite *s = suite_create("memchr");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_memchr_1);
  tcase_add_test(tc, test_memchr_2);
  tcase_add_test(tc, test_memchr_3);
  tcase_add_test(tc, test_memchr_4);
  tcase_add_test(tc, test_memchr_5);

  suite_add_tcase(s, tc);
  return s;
}
