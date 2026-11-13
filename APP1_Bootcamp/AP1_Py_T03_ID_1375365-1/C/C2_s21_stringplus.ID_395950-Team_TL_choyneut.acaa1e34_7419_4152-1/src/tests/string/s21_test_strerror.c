#include <check.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_strerror_zero) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
}
END_TEST

START_TEST(test_strerror_mid) {
  ck_assert_str_eq(s21_strerror(5), strerror(5));
}
END_TEST

START_TEST(test_strerror_max) {
  ck_assert_str_eq(s21_strerror(133), strerror(133));
}
END_TEST

START_TEST(test_strerror_negative) {
  char *my = s21_strerror(-1);
  char *sys = strerror(-1);
  ck_assert_str_eq(my, sys);
}
END_TEST

START_TEST(test_strerror_out_of_range) {
  char *my = s21_strerror(999);
  char *sys = strerror(999);
  ck_assert_str_eq(my, sys);
}
END_TEST

Suite *strerror_suite(void) {
  Suite *s = suite_create("s21_strerror");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strerror_zero);
  tcase_add_test(tc, test_strerror_mid);
  tcase_add_test(tc, test_strerror_max);
  tcase_add_test(tc, test_strerror_negative);
  tcase_add_test(tc, test_strerror_out_of_range);

  suite_add_tcase(s, tc);
  return s;
}