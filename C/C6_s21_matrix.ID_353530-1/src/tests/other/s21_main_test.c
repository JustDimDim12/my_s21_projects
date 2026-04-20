#include <check.h>

Suite *calc_complements_suite(void);
Suite *determinant_suite(void);

int main() {
  SRunner *sr = srunner_create(calc_complements_suite());
  srunner_add_suite(sr, determinant_suite());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}