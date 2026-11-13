#include <check.h>

Suite *eq_suite(void);
Suite *sum_suite(void);
Suite *sub_suite(void);
Suite *mult_number_suite(void);
Suite *mult_matrix_suite(void);

int main() {
  SRunner *sr = srunner_create(eq_suite());
  srunner_add_suite(sr, sum_suite());
  srunner_add_suite(sr, sub_suite());
  srunner_add_suite(sr, mult_number_suite());
  srunner_add_suite(sr, mult_matrix_suite());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}