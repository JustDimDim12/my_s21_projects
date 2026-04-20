#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_memset_full_string) {
  char str[7] = "abcdef";
  char expected[7];
  memset(expected, 'x', 6);
  ck_assert_ptr_eq(s21_memset(str, 'x', 6), str);
  ck_assert_mem_eq(str, expected, 6);
}
END_TEST

START_TEST(test_memset_partial) {
  char str[7] = "abcdef";
  char expected[7] = "xxxdef";
  ck_assert_ptr_eq(s21_memset(str, 'x', 3), str);
  ck_assert_mem_eq(str, expected, 7);
}
END_TEST

START_TEST(test_memset_zero_n) {
  char str[7] = "abcdef";
  char expected[7] = "abcdef";
  ck_assert_ptr_eq(s21_memset(str, 'x', 0), str);
  ck_assert_mem_eq(str, expected, 6);
}
END_TEST

START_TEST(test_memset_empty) {
  char str[1] = "";
  ck_assert_ptr_eq(s21_memset(str, 'x', 1), str);
  ck_assert_int_eq(str[0], 'x');
}
END_TEST

START_TEST(test_memset_int_array) {
  int arr[5] = {1, 2, 3, 4, 5};
  int expected[5] = {0};
  ck_assert_ptr_eq(s21_memset(arr, 0, 5 * sizeof(int)), arr);
  for (int i = 0; i < 5; i++) {
    ck_assert_int_eq(arr[i], expected[i]);
  }
}
END_TEST

Suite *memset_suite(void) {
  Suite *s = suite_create("memset");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_memset_full_string);
  tcase_add_test(tc, test_memset_partial);
  tcase_add_test(tc, test_memset_zero_n);
  tcase_add_test(tc, test_memset_empty);
  tcase_add_test(tc, test_memset_int_array);

  suite_add_tcase(s, tc);
  return s;
}
