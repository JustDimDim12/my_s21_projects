#include <check.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "../../s21_string.h"

START_TEST(test_d_basic) {
  char buf1[512], buf2[512];
  int val = 123;
  s21_sprintf(buf1, "%d", val);
  sprintf(buf2, "%d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_d_negative) {
  char buf1[512], buf2[512];
  int val = -456;
  s21_sprintf(buf1, "%d", val);
  sprintf(buf2, "%d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_d_zero) {
  char buf1[512], buf2[512];
  int val = 0;
  s21_sprintf(buf1, "%d", val);
  sprintf(buf2, "%d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_i_basic) {
  char buf1[512], buf2[512];
  int val = 123;
  s21_sprintf(buf1, "%i", val);
  sprintf(buf2, "%i", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_u_basic) {
  char buf1[512], buf2[512];
  unsigned int val = 12345;
  s21_sprintf(buf1, "%u", val);
  sprintf(buf2, "%u", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_u_max) {
  char buf1[512], buf2[512];
  unsigned int val = UINT_MAX;
  s21_sprintf(buf1, "%u", val);
  sprintf(buf2, "%u", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_x_basic) {
  char buf1[512], buf2[512];
  int val = 255;
  s21_sprintf(buf1, "%x", val);
  sprintf(buf2, "%x", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_X_basic) {
  char buf1[512], buf2[512];
  int val = 255;
  s21_sprintf(buf1, "%X", val);
  sprintf(buf2, "%X", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_o_basic) {
  char buf1[512], buf2[512];
  int val = 64;
  s21_sprintf(buf1, "%o", val);
  sprintf(buf2, "%o", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_f_basic) {
  char buf1[512], buf2[512];
  double val = 3.14159;
  s21_sprintf(buf1, "%f", val);
  sprintf(buf2, "%f", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_e_basic) {
  char buf1[512], buf2[512];
  double val = 12345.6789;
  s21_sprintf(buf1, "%e", val);
  sprintf(buf2, "%e", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_E_basic) {
  char buf1[512], buf2[512];
  double val = 12345.6789;
  s21_sprintf(buf1, "%E", val);
  sprintf(buf2, "%E", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_g_basic) {
  char buf1[512], buf2[512];
  double val = 123.456;
  s21_sprintf(buf1, "%g", val);
  sprintf(buf2, "%g", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_G_basic) {
  char buf1[512], buf2[512];
  double val = 0.0001234;
  s21_sprintf(buf1, "%G", val);
  sprintf(buf2, "%G", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_c_basic) {
  char buf1[10], buf2[10];
  char val = 'A';
  s21_sprintf(buf1, "%c", val);
  sprintf(buf2, "%c", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s_basic) {
  char buf1[512], buf2[512];
  char *val = "Hello, world!";
  s21_sprintf(buf1, "%s", val);
  sprintf(buf2, "%s", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s_null) {
  char buf1[512], buf2[512];
  char *val = NULL;
  s21_sprintf(buf1, "%s", val);
  sprintf(buf2, "%s", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_p_basic) {
  char buf1[512], buf2[512];
  void *ptr = (void *)0x1234abcd;
  s21_sprintf(buf1, "%p", ptr);
  sprintf(buf2, "%p", ptr);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_percent) {
  char buf1[10], buf2[10];
  s21_sprintf(buf1, "%%");
  sprintf(buf2, "%%");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_flag_plus) {
  char buf1[512], buf2[512];
  int val = 42;
  s21_sprintf(buf1, "%+d", val);
  sprintf(buf2, "%+d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_flag_minus) {
  char buf1[512], buf2[512];
  int val = 42;
  s21_sprintf(buf1, "%-8d", val);
  sprintf(buf2, "%-8d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_flag_space) {
  char buf1[512], buf2[512];
  int val = 42;
  s21_sprintf(buf1, "% d", val);
  sprintf(buf2, "% d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_flag_zero) {
  char buf1[512], buf2[512];
  int val = 42;
  s21_sprintf(buf1, "%08d", val);
  sprintf(buf2, "%08d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_flag_hash_hex) {
  char buf1[512], buf2[512];
  int val = 255;
  s21_sprintf(buf1, "%#x", val);
  sprintf(buf2, "%#x", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_flag_hash_octal) {
  char buf1[512], buf2[512];
  int val = 64;
  s21_sprintf(buf1, "%#o", val);
  sprintf(buf2, "%#o", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_width) {
  char buf1[512], buf2[512];
  int val = 42;
  s21_sprintf(buf1, "%10d", val);
  sprintf(buf2, "%10d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_precision) {
  char buf1[512], buf2[512];
  double val = 3.14159;
  s21_sprintf(buf1, "%.2f", val);
  sprintf(buf2, "%.2f", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_width_precision) {
  char buf1[512], buf2[512];
  double val = 3.14159;
  s21_sprintf(buf1, "%10.2f", val);
  sprintf(buf2, "%10.2f", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_width_star) {
  char buf1[512], buf2[512];
  int val = 42, width = 10;
  s21_sprintf(buf1, "%*d", width, val);
  sprintf(buf2, "%*d", width, val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_precision_star) {
  char buf1[512], buf2[512];
  double val = 3.14159;
  int prec = 2;
  s21_sprintf(buf1, "%.*f", prec, val);
  sprintf(buf2, "%.*f", prec, val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_length_h) {
  char buf1[512], buf2[512];
  short val = 12345;
  s21_sprintf(buf1, "%hd", val);
  sprintf(buf2, "%hd", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_length_l) {
  char buf1[512], buf2[512];
  long val = 123456789L;
  s21_sprintf(buf1, "%ld", val);
  sprintf(buf2, "%ld", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_length_L) {
  char buf1[512], buf2[512];
  long double val = 3.1415926535L;
  s21_sprintf(buf1, "%Lf", val);
  sprintf(buf2, "%Lf", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_comb_flags_plus_zero) {
  char buf1[512], buf2[512];
  int val = 42;
  s21_sprintf(buf1, "%+08d", val);
  sprintf(buf2, "%+08d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_comb_flags_minus_plus) {
  char buf1[512], buf2[512];
  int val = 42;
  s21_sprintf(buf1, "%-+10d", val);
  sprintf(buf2, "%-+10d", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_comb_flags_hash_zero) {
  char buf1[512], buf2[512];
  int val = 255;
  s21_sprintf(buf1, "%#08x", val);
  sprintf(buf2, "%#08x", val);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_int_limits) {
  char buf1[512], buf2[512];
  s21_sprintf(buf1, "%d %d", INT_MAX, INT_MIN);
  sprintf(buf2, "%d %d", INT_MAX, INT_MIN);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_uint_limits) {
  char buf1[512], buf2[512];
  s21_sprintf(buf1, "%u", UINT_MAX);
  sprintf(buf2, "%u", UINT_MAX);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_double_limits) {
  char buf1[512], buf2[512];
  s21_sprintf(buf1, "%f %f", DBL_MAX, DBL_MIN);
  sprintf(buf2, "%f %f", DBL_MAX, DBL_MIN);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_complex_1) {
  char buf1[1024], buf2[1024];
  int i = 123;
  double d = 456.789;
  char *s = "Test";
  s21_sprintf(buf1, "Int:%08d Double:%10.3f String:%-10s Char:%c", i, d, s,
              'X');
  sprintf(buf2, "Int:%08d Double:%10.3f String:%-10s Char:%c", i, d, s, 'X');
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_complex_2) {
  char buf1[1024], buf2[1024];
  s21_sprintf(buf1, "%d %u %x %o %f %e %g %c %s %%", -123, 456, 255, 64, 3.14,
              1.23e4, 0.0000123, 'A', "hello");
  sprintf(buf2, "%d %u %x %o %f %e %g %c %s %%", -123, 456, 255, 64, 3.14,
          1.23e4, 0.0000123, 'A', "hello");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_d_basic);
  tcase_add_test(tc_core, test_d_negative);
  tcase_add_test(tc_core, test_d_zero);
  tcase_add_test(tc_core, test_i_basic);
  tcase_add_test(tc_core, test_u_basic);
  tcase_add_test(tc_core, test_u_max);
  tcase_add_test(tc_core, test_x_basic);
  tcase_add_test(tc_core, test_X_basic);
  tcase_add_test(tc_core, test_o_basic);
  tcase_add_test(tc_core, test_f_basic);
  tcase_add_test(tc_core, test_e_basic);
  tcase_add_test(tc_core, test_E_basic);
  tcase_add_test(tc_core, test_g_basic);
  tcase_add_test(tc_core, test_G_basic);
  tcase_add_test(tc_core, test_c_basic);
  tcase_add_test(tc_core, test_s_basic);
  tcase_add_test(tc_core, test_s_null);
  tcase_add_test(tc_core, test_p_basic);
  tcase_add_test(tc_core, test_percent);

  tcase_add_test(tc_core, test_flag_plus);
  tcase_add_test(tc_core, test_flag_minus);
  tcase_add_test(tc_core, test_flag_space);
  tcase_add_test(tc_core, test_flag_zero);
  tcase_add_test(tc_core, test_flag_hash_hex);
  tcase_add_test(tc_core, test_flag_hash_octal);

  tcase_add_test(tc_core, test_width);
  tcase_add_test(tc_core, test_precision);
  tcase_add_test(tc_core, test_width_precision);
  tcase_add_test(tc_core, test_width_star);
  tcase_add_test(tc_core, test_precision_star);

  tcase_add_test(tc_core, test_length_h);
  tcase_add_test(tc_core, test_length_l);
  tcase_add_test(tc_core, test_length_L);

  tcase_add_test(tc_core, test_comb_flags_plus_zero);
  tcase_add_test(tc_core, test_comb_flags_minus_plus);
  tcase_add_test(tc_core, test_comb_flags_hash_zero);

  tcase_add_test(tc_core, test_int_limits);
  tcase_add_test(tc_core, test_uint_limits);
  tcase_add_test(tc_core, test_double_limits);

  tcase_add_test(tc_core, test_complex_1);
  tcase_add_test(tc_core, test_complex_2);

  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  SRunner *sr = srunner_create(s21_sprintf_suite());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}