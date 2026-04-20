#include <check.h>

Suite *transpose_suite(void);
Suite *inverse_suite(void);

int main() {
  SRunner *sr = srunner_create(transpose_suite());
  srunner_add_suite(sr, inverse_suite());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}