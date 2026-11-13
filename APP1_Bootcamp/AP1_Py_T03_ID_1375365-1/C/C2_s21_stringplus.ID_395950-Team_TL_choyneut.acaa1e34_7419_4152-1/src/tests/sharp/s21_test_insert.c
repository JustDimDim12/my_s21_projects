#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../../s21_string.h"

// Вставка в середину строки
START_TEST(test_insert_middle) {
  char src[] = "HelloWorld";
  char str[] = "Beautiful";
  char *res = s21_insert(src, str, 5);
  ck_assert_str_eq(res, "HelloBeautifulWorld");
  free(res);
}
END_TEST

// Вставка в начало
START_TEST(test_insert_start) {
  char src[] = "World";
  char str[] = "Hello";
  char *res = s21_insert(src, str, 0);
  ck_assert_str_eq(res, "HelloWorld");
  free(res);
}
END_TEST

// Вставка в конец
START_TEST(test_insert_end) {
  char src[] = "Hello";
  char str[] = "World";
  char *res = s21_insert(src, str, 5);
  ck_assert_str_eq(res, "HelloWorld");
  free(res);
}
END_TEST

// Вставка пустой строки
START_TEST(test_insert_empty_str) {
  char src[] = "Hello";
  char str[] = "";
  char *res = s21_insert(src, str, 2);
  ck_assert_str_eq(res, "Hello");
  free(res);
}
END_TEST

// Индекс больше длины исходной строки
START_TEST(test_insert_out_of_range) {
  char src[] = "Hello";
  char str[] = "World";
  char *res = s21_insert(src, str, 10);
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

Suite *insert_suite(void) {
  Suite *s = suite_create("insert");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_insert_middle);
  tcase_add_test(tc, test_insert_start);
  tcase_add_test(tc, test_insert_end);
  tcase_add_test(tc, test_insert_empty_str);
  tcase_add_test(tc, test_insert_out_of_range);

  suite_add_tcase(s, tc);
  return s;
}
