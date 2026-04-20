#include <check.h>

Suite *matrix_alive_suite(void);
Suite *nullize_suite(void);
Suite *minor_suite(void);

int main() {
  SRunner *sr = srunner_create(matrix_alive_suite());
  srunner_add_suite(sr, nullize_suite());
  srunner_add_suite(sr, minor_suite());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}