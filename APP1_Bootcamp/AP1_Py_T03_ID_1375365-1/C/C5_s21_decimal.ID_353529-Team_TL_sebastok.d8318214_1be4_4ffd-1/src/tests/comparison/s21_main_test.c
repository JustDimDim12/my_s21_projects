#include <check.h>

Suite *is_equal_suite(void);
Suite *is_less_suite(void);
Suite *is_less_or_equal_suite(void);
Suite *is_not_equal_suite(void);
Suite *is_greater_suite(void);
Suite *is_greater_or_equal_suite(void);

int main() {
  SRunner *sr = srunner_create(is_equal_suite());
  srunner_add_suite(sr, is_not_equal_suite());
  srunner_add_suite(sr, is_less_suite());
  srunner_add_suite(sr, is_less_or_equal_suite());
  srunner_add_suite(sr, is_greater_suite());
  srunner_add_suite(sr, is_greater_or_equal_suite());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}