#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_memcpy_basic) {
  char src[] = "abcdef";
  char dest[7] = {0};
  ck_assert_ptr_eq(s21_memcpy(dest, src, 7), memcpy(dest, src, 7));
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_memcpy_partial) {
  char src[] = "abcdef";
  char dest[7] = {0};
  ck_assert_ptr_eq(s21_memcpy(dest, src, 3), memcpy(dest, src, 3));
  ck_assert_mem_eq(dest, src, 3);
}
END_TEST

START_TEST(test_memcpy_zero_n) {
  char src[] = "abcdef";
  char dest[7] = {0};
  ck_assert_ptr_eq(s21_memcpy(dest, src, 0), memcpy(dest, src, 0));
}
END_TEST

START_TEST(test_memcpy_empty) {
  char src[] = "";
  char dest[1] = {0};
  ck_assert_ptr_eq(s21_memcpy(dest, src, 1), memcpy(dest, src, 1));
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_memcpy_int_array) {
  int src[] = {1, 2, 3, 4, 5};
  int dest[5] = {0};
  ck_assert_ptr_eq(s21_memcpy(dest, src, 5 * sizeof(int)),
                   memcpy(dest, src, 5 * sizeof(int)));
  for (int i = 0; i < 5; i++) {
    ck_assert_int_eq(dest[i], src[i]);
  }
}
END_TEST

Suite *memcpy_suite(void) {
  Suite *s = suite_create("memcpy");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_memcpy_basic);
  tcase_add_test(tc, test_memcpy_partial);
  tcase_add_test(tc, test_memcpy_zero_n);
  tcase_add_test(tc, test_memcpy_empty);
  tcase_add_test(tc, test_memcpy_int_array);

  suite_add_tcase(s, tc);
  return s;
}
